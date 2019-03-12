#version 430 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uv;

layout (binding = 0) uniform sampler2D tex;
out vec4 color;

uniform float aperture;

void main()
{
    color = vec4(texture(tex, uv).xyz / aperture, 1);
    //color = vec4(uv * 1, 0, 1);
}