#version 430 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv_albedo;
layout (location = 3) in vec2 uv_lightmap;

layout (binding = 0) uniform sampler2D tex_lightmap;
layout (binding = 1) uniform sampler2D tex_albedo;

out vec4 color;

uniform float aperture;
uniform vec3 l;

float shlick(float cosnv)
{
    float n1 = 1.0;
    float n2 = 1.333;
    float r0 = ((n1 - n2) / (n1 + n2));
    float r0_sq = r0 * r0;

    return r0 + (1.0 - r0_sq) * pow(1 - cosnv, 5.0);
}

void main(void)
{
    vec3 v = vec3(1.0);
    vec3 r = 2 * dot(normal, l) * normal - l;
	vec3 blue = (vec3(94.0, 155.0, 255.0) / 255.0) * 0.001;
	vec3 light = texture(tex_lightmap, uv_lightmap).xyz + blue;

	color = vec4(light * texture(tex_albedo, uv_albedo).xyz, 1.0) + shlick(dot(r, v)) * vec4(0.1);
}
