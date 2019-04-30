#version 430 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv_albedo;

layout (binding = 0) uniform sampler2D tex_albedo;

layout (location = 0) out vec4 color;
layout (location = 1) out vec4 dist;

uniform float aperture;
uniform vec3 l_dir;
uniform vec3 p_cam;

void main(void)
{
    vec3 blue = vec3(0.0, 1.0, 0.0);
	vec3 light;
    vec3 v = normalize(p_cam - pos);
    vec3 yellow = vec3(0.7, 1.0, 0.3);
    vec4 tex = texture(tex_albedo, uv_albedo);
    vec3 n = normal;

    if (dot(normal, v) < 0.0)
        n *= -1.0;
    float ill = max(0.0, dot(n, l_dir));
    light = vec3(ill) * yellow + (1.0 - ill) * blue;
    if (tex.w < 0.05)
        discard;
	color = vec4(light * tex.xyz, tex.w);
    dist = vec4(vec3(p_cam - pos), 1.0);
}
