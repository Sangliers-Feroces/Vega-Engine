#version 430 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 uv;

layout(location = 0) out vec3 pos_out;
layout(location = 1) out vec2 uv_out;

void main() {
    vec3 pos = vertexPosition_modelspace;
    pos.z += 5;
    gl_Position =
    vec4(pos.xy / pos.z, pos.z / 100, 1.0);
    pos_out = pos;
    uv_out = uv;
    /*gl_Position.xyz = vertexPosition_modelspace;
    gl_Position.w = 1.0;*/
}