/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** ui
*/

#include "headers.h"

void ui_init(demo_t *demo)
{
    const vec2 vertex_array_base[] =
    {{0.0f, 0.0f},
    {0.0f, 1.0f},
    {1.0f, 0.0f},
    {0.0f, 1.0f},
    {1.0f, 1.0f},
    {1.0f, 0.0f}};

    _ui.ratiowh = demo->cam.ratiowh;
    _ui.ui_program = shader_load_vert_frag("src/gpu/shader/ui_vertex.glsl",
    "src/gpu/shader/ui_fragment.glsl");
    _ui.tex = texture2_load("res/ui/elon.jpg");
    glGenBuffers(1, &_ui.vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, _ui.vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * 6,
    (glvoid*)vertex_array_base, GL_STATIC_DRAW);
}

void ui_quit(void)
{
    texture2_destroy(_ui.tex);
    glDeleteBuffers(1, &_ui.vertex_buffer);
    glDeleteProgram(_ui.ui_program);
}
