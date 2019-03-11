#version 450

layout(local_size_x = 1, local_size_y = 1) in;

layout(r32i, binding = 0) uniform iimage2D mem;
layout(rgba32f, binding = 1) uniform image2D lightmap;

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

struct bounds3 {
	vec3 min;
	vec3 max;
};

struct inter_ray3 {
	int triangle;
	vec3 p;
	vec3 bar;
	float min_t;
};

#define FLT_INF (uintBitsToFloat(uint(0x7F800000)))

int mem_stride;

void init(void)
{
	mem_stride = imageSize(mem).x;
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

vec3 read_vec3(int ptr)
{
	return vec3(read_float(ptr), read_float(ptr + 1), read_float(ptr + 2));
}

bounds3 read_bounds3(int ptr)
{
	return bounds3(read_vec3(ptr), read_vec3(ptr + 3));
}

frame stack[256];
int stack_ndx;

#define local_ptr stack[stack_ndx].ptr
#define local_iter stack[stack_ndx].iter

inter_ray3 inter_buf;
ray3 ray_buf;

void intersect_ray_triangle(int ptr)
{
	
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
	if (local_ptr == 0) {
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

inter_ray3 octree_intersect_ray(ray3 ray)
{
	inter_buf = inter_ray3(-1, vec3(0.0), vec3(0.0), 0.0);
	ray_buf = ray;
	stack_ndx = -1;
	proc_call(16);
	while (stack_ndx >= 0)
		intersect_ray_actual();
	return inter_buf;
}

void write_value_lightmap(int value)
{
	ivec2 size = imageSize(lightmap);
	for (int i = 0; i < size.y; i++) {
		int j = 0;
		//for (int j = 0; j < size.x; j++)
			imageStore(lightmap, ivec2(j, i), vec4(value));
	}
}

int count;

void main(void)
{
	init();
	int to_write = 5;
	count = 53;

	octree_intersect_ray(ray3(vec3(1.0), vec3(1.0)));
	write_value_lightmap(count);
	/*for (int i = 0; i < size.y; i++)
		for (int j = 0; j < size.x; j++) {
			if (((i & 1) ^ (j & 1)) != 0)
				imageStore(lightmap, ivec2(j, i), vec4(1.0f, 0.0f, 0.0f, 0.0f));
			else
				imageStore(lightmap, ivec2(j, i), vec4(1.0f, 0.0f, 1.0f, 0.0f));
			}*/
	
}
