#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;

void main() {
    /*gl_Position =
    vec4(vec2(vertexPosition_modelspace.xy) / vertexPosition_modelspace.z, vertexPosition_modelspace.z, 1.0);
    */
    gl_Position.xyz = vertexPosition_modelspace;
    gl_Position.w = 1.0;
}