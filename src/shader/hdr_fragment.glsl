#version 430 core

layout (location = 0) in vec2 uv;

layout (binding = 0) uniform sampler2D tex;
layout (binding = 1) uniform sampler2D dist;

out vec4 color;

float fog_ratio(void)
{
    return 1.0 - 1.0 / exp(texture(dist, uv).x * 0.0003);
}

void main(void)
{
    float gamma = 1.1;
    float exposure = 1.0;
    vec3 hdr = texture(tex, uv).xyz;
	vec3 blue = vec3(94.0 / 1.5, 155.0 / 1.5, 255.0) / 255.0;
    float fog = fog_ratio();

    hdr = hdr * (1.0 - fog) + blue * fog;
    vec3 mapped = vec3(1.0) - exp(-hdr * exposure);
    color = vec4(pow(mapped, vec3(1.0 / gamma)), 1.0);
}
