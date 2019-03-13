/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** ui
*/

#include "headers.h"

const vec2 vertex_array_base[] = {
    {0, 0},
    {0, 1},
    {1, 0},
    {0, 1},
    {1, 1},
    {1, 0},
};

void set_ui(void)
{
    _ui.ui_program = shader_load_vert_frag("src/gpu/shader/ui_vertex.glsl",
    "src/gpu/shader/ui_fragment.glsl");
    _ui.tex = texture2_load("res/ui/elon.jpg");
    glGenBuffers(1, &_ui.vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, _ui.vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * 6,
    (glvoid *)vertex_array_base, GL_STATIC_DRAW);
}

static void draw_quad(vec2 pos, vec2 size)
{
    gluint pos_id = glGetUniformLocation(_ui.ui_program, "pos");
    gluint size_id = glGetUniformLocation(_ui.ui_program, "size");

    glUniform2fv(pos_id, 1, (glfloat *)&pos);
    glUniform2fv(size_id, 1, (glfloat *)&size);
    glBindBuffer(GL_ARRAY_BUFFER, _ui.vertex_buffer);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
    sizeof(vec2), BUFFER_OFFSET(0));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _ui.tex->id);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(0);
}

void display_ui(int task, demo_t *demo)
{
    glUseProgram(_ui.ui_program);

    draw_quad((vec2){-1.0f, 1.0f}, (vec2){0.15f, 0.25f});
    draw_quad((vec2){-0.85f, 1.0f}, (vec2){0.05f, 0.25f});
    draw_quad((vec2){-0.90f, 0.975f}, (vec2){0.75f, 0.20f});
}
