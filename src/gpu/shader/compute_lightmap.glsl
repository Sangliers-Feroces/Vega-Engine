#version 430

layout(local_size_x = 1, local_size_y = 1) in;

layout(r32i, binding = 0) uniform readonly iimage2D mem;
layout(rgba32f, binding = 1) uniform restrict image2D lightmap;

struct frame {
	int ptr;	// octree pointer
	int iter;	// iteration, from 0 to 7 (complete at 8)
};

struct ray1 {
	float p;
	float v;
};

struct ray3 {
	vec3 p;
	vec3 v;
};

struct ray3_color {
	ray3 ray;
	vec3 color;
};

struct bounds3 {
	vec3 min;
	vec3 max;
};

struct rtx_triangle {
	vec3 vertex[3];
	vec2 uv[3];
	vec3 normal;
	vec3 tangent;
	vec3 bitangent;
};

struct inter_ray3 {
	int triangle;
	vec3 p;
	vec3 bar;
	float min_t;
};

int read(int ptr);

#define FLT_INF (uintBitsToFloat(uint(0x7F800000)))
#define NULL 0
#define M_PI (3.14159265358979323846)

uint rand_seed;
uint thread_count;
uint rays_count;

uint rand_hash(uint x)
{
	x += ( x << 10u );
	x ^= ( x >>  6u );
	x += ( x <<  3u );
	x ^= ( x >> 11u );
	x += ( x << 15u );
	return x;
}

float randf_actual(uint m)
{
	const uint ieeeMantissa = 0x007FFFFFu; // binary32 mantissa bitmask
	const uint ieeeOne      = 0x3F800000u; // 1.0 in IEEE binary32

	m &= ieeeMantissa;                     // Keep only mantissa bits (fractional part)
	m |= ieeeOne;                          // Add fractional part to 1.0

	float f = uintBitsToFloat(m);       // Range [1:2]
	return f - 1.0;                        // Range [0:1]
}

float randf(void)
{
	rand_seed++;
	return randf_actual(rand_hash(rand_seed++));
}

int mem_stride;
vec2 texture_size;

void init(void)
{
	mem_stride = imageSize(mem).x;
	thread_count = gl_GlobalInvocationID.x;
	rand_seed = uint(read(0)) + gl_WorkGroupID.x * 172721;
	rays_count = read(1);
	texture_size = imageSize(lightmap);
}

ivec2 ndx_to_2d(int ndx)
{
	return ivec2(ndx % mem_stride, ndx / mem_stride);
}

int read(int ptr)
{
	return imageLoad(mem, ndx_to_2d(ptr)).x;
}

float read_float(int ptr)
{
	return intBitsToFloat(read(ptr));
}

vec2 read_vec2(int ptr)
{
	return vec2(read_float(ptr), read_float(ptr + 1));
}

vec3 read_vec3(int ptr)
{
	return vec3(read_float(ptr), read_float(ptr + 1), read_float(ptr + 2));
}

bounds3 read_bounds3(int ptr)
{
	return bounds3(read_vec3(ptr), read_vec3(ptr + 3));
}

rtx_triangle read_rtx_triangle(int ptr)
{
	return rtx_triangle(vec3[3](read_vec3(ptr), read_vec3(ptr + 3), read_vec3(ptr + 6)),
	vec2[3](read_vec2(ptr + 9), read_vec2(ptr + 9 + 2), read_vec2(ptr + 9 + 4)),
	read_vec3(ptr + 16), read_vec3(ptr + 16 + 3), read_vec3(ptr + 16 + 6));
}

vec3 ray3_compute(ray3 ray, float t)
{
	return ray.p + ray.v * t;
}

bool is_float_in_0_1(float value)
{
	return ((value >= 0.0) && (value <= 1.0));
}

bool is_barycentric_valid(vec3 bar)
{
	return (is_float_in_0_1(bar.x) && is_float_in_0_1(bar.y) &&
	is_float_in_0_1(bar.z));
}

vec3 barycentric3(vec3 p, vec3[3] triangle)
{
	vec3 v0 = triangle[1] - triangle[0];
	vec3 v1 = triangle[2] - triangle[0];
	vec3 v2 = p - triangle[0];
	float dot00 = dot(v0, v0);
	float dot01 = dot(v0, v1);
	float dot11 = dot(v1, v1);
	float dot20 = dot(v2, v0);
	float dot21 = dot(v2, v1);
	float div = dot00 * dot11 - dot01 * dot01;
	vec3 res;

	res.y = (dot11 * dot20 - dot01 * dot21) / div;
	res.z = (dot00 * dot21 - dot01 * dot20) / div;
	res.x = 1.0f - res.y - res.z;
	return res;
}

frame stack[256];
int stack_ndx;

#define local_ptr stack[stack_ndx].ptr
#define local_iter stack[stack_ndx].iter

inter_ray3 inter_buf;
ray3 ray_buf;
rtx_triangle triangle_buf;
rtx_triangle triangle_inter;

float intersect_plane(float dotnv)
{
	return dot(triangle_buf.normal, triangle_buf.vertex[0] - ray_buf.p) / dotnv;
}

void intersect_ray_triangle(int ptr)
{
	triangle_buf = read_rtx_triangle(ptr);
	float dotnv = dot(triangle_buf.normal, ray_buf.v);
	float t;
	vec3 p;
	vec3 bar;

	if (dotnv >= 0.0)
		return;
	t = intersect_plane(dotnv);
	if (t <= 0.0)
		return;
	p = ray3_compute(ray_buf, t);
	bar = barycentric3(p, triangle_buf.vertex);
	if (!is_barycentric_valid(bar))
		return;
	if ((inter_buf.triangle == NULL) || (t < inter_buf.min_t)) {
		triangle_inter = triangle_buf;
		inter_buf.triangle = ptr;
		inter_buf.p = p;
		inter_buf.bar = bar;
		inter_buf.min_t = t;
	}
}

void intersect_ray_vec_triangle(int ptr)
{
	int count = read(ptr);
	int start = ptr + 1;

	for (int i = 0; i < count; i++)
		intersect_ray_triangle(start + i * 25);
}

bounds3 bounds_buf;
vec2 t_buf;

bool ray1d_bound_inside(ray1 r, float b_min, float b_max)
{
	if (r.v < 0.0f) {
		t_buf.x = max(t_buf.x, (b_max - r.p) / r.v);
		t_buf.y = min(t_buf.y, (b_min - r.p) / r.v);
	} else {
		t_buf.x = max(t_buf.x, (b_min - r.p) / r.v);
		t_buf.y = min(t_buf.y, (b_max - r.p) / r.v);
	}
	return true;
}

bool ray1d_bound(ray1 r, float b_min, float b_max)
{
	if (r.v == 0.0f)
		return ((r.p >= b_min) && (r.p < b_max));
	if (r.p < b_min) {
		t_buf.x = max(t_buf.x, (b_min - r.p) / r.v);
		t_buf.y = min(t_buf.y, (b_max - r.p) / r.v);
		return (r.v > 0.0f);
	} else if (r.p >= b_max) {
		t_buf.x = max(t_buf.x, (b_max - r.p) / r.v);
		t_buf.y = min(t_buf.y, (b_min - r.p) / r.v);
		return (r.v < 0.0f);
	} else
		return ray1d_bound_inside(r, b_min, b_max);
}

bool is_ray_in_bounds(void)
{
	vec2 t_buf = vec2(-FLT_INF, FLT_INF);

	if (!ray1d_bound(ray1(ray_buf.p.x, ray_buf.v.x), bounds_buf.min.x, bounds_buf.max.x))
		return false;
	if (!ray1d_bound(ray1(ray_buf.p.y, ray_buf.v.y), bounds_buf.min.y, bounds_buf.max.y))
		return false;
	if (!ray1d_bound(ray1(ray_buf.p.z, ray_buf.v.z), bounds_buf.min.z, bounds_buf.max.z))
		return false;
	return (t_buf.x <= t_buf.y);
}

void proc_call(int ptr)
{
	stack_ndx++;
	stack[stack_ndx] = frame(ptr, 0);
}

void proc_return(void)
{
	stack_ndx--;
}

void intersect_ray_actual(void)
{
	if (local_ptr == NULL) {
		proc_return();
		return;
	}
	bounds_buf = read_bounds3(local_ptr + 8);
	if (!is_ray_in_bounds()) {
		proc_return();
		return;
	}
	if (local_iter < 8) {
		int to_send = read(local_ptr + local_iter);
		local_iter++;
		proc_call(to_send);
		return;
	}
	intersect_ray_vec_triangle(read(local_ptr + 14));
	proc_return();
	return;
}

inter_ray3 octree_intersect_ray(void)
{
	inter_buf = inter_ray3(NULL, vec3(0.0), vec3(0.0), 0.0);
	stack_ndx = -1;
	proc_call(16);
	while (stack_ndx >= 0)
		intersect_ray_actual();
	return inter_buf;
}

vec3 diffuse_ray(void)
{
	float n = 1.0f;
	float x = 2.0f * M_PI * randf();
	float y = acos(pow(randf(), 1.0f / (n + 1.0f)));

	return (triangle_buf.tangent * sin(y) * cos(x)) +
	(triangle_buf.bitangent * sin(y) * sin(x)) +
	(triangle_buf.normal * cos(y));
}

vec2 barycentric2_get_point(vec2[3] triangle, vec3 bar)
{
	return (triangle[0] * bar.x) + (triangle[1] * bar.y) + (triangle[2] * bar.z);
}

ivec2 texture2_get_nearest(vec2 p)
{
	return ivec2((p * texture_size) + vec2(0.5f, 0.5f));
}

void texture2f_write_color_bar(vec2[3] uv, vec3 bar, vec3 color)
{
	vec2 p = barycentric2_get_point(uv, bar);
	ivec2 pos;

	pos = texture2_get_nearest(p);
	vec4 to_write = imageLoad(lightmap, pos) + vec4(color, 0.0);
	imageStore(lightmap, pos, to_write);
}

void throw_ray(ray3_color ray)
{
	for (int i = 0; i < 16; i++) {
		ray_buf = ray.ray;
		inter_ray3 inter = octree_intersect_ray();
		if (inter.triangle == NULL)
			return;
		texture2f_write_color_bar(triangle_inter.uv, inter.bar, ray.color);
		ray.ray.p = inter.p;
		ray.ray.v = diffuse_ray();
		ray.color *= 0.75f;
	}
}

void write_value_lightmap(float value)
{
	ivec2 size = imageSize(lightmap);
	for (int i = 0; i < size.y; i++) {
		int j = 0;
		//for (int j = 0; j < size.x; j++)
			imageStore(lightmap, ivec2(j, i), vec4(value));
	}
}

void write_value_lightmap(vec4 value)
{
	ivec2 size = imageSize(lightmap);
	for (int i = 0; i < size.y; i++) {
		int j = 0;
		//for (int j = 0; j < size.x; j++)
			imageStore(lightmap, ivec2(j, i), value);
	}
}

void main(void)
{
	init();
	//int to_write = 5;

	for (uint i = 0; i < rays_count; i++)
		throw_ray(ray3_color(ray3(vec3(randf() * 100.0f - 50.0f, 50.0f, -randf() * 100.0f),
		vec3(1.0f, -1.0f, 1.0f)), vec3(1.0f, 1.0f, 1.0f)));
	//octree_intersect_ray(ray3(vec3(0.0, 0.0, -2.5), vec3(0.2, 0.5, 1.7)));
	//write_value_lightmap(vec4(inter_buf.p, 0.0));
	//write_value_lightmap(inter_buf.min_t);
	//write_value_lightmap(inter_buf.min_t);
	/*for (int i = 0; i < size.y; i++)
		for (int j = 0; j < size.x; j++) {
			if (((i & 1) ^ (j & 1)) != 0)
				imageStore(lightmap, ivec2(j, i), vec4(1.0f, 0.0f, 0.0f, 0.0f));
			else
				imageStore(lightmap, ivec2(j, i), vec4(1.0f, 0.0f, 1.0f, 0.0f));
			}*/
	
}
