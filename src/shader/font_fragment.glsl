#version 430 core

layout (location = 0) in vec2 uv;
layout (binding = 0) uniform sampler2D tex;

out vec4 color;

uniform vec2 tex_pos;
uniform vec2 tex_size;

void main()
{
    vec2 new_pos = {8.0, 1.0};

    color = texture(tex, new_pos + vec2(uv.x, -uv.y) * tex_size);
}