/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** ui
*/

#include "headers.h"

void ui_draw_full_rel(texture2 *texture, vec2 pos, vec2 size)
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
    glBindTexture(GL_TEXTURE_2D, texture->id);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(0);
}

void ui_draw_x(texture2 *texture, vec2 pos, float size)
{
    vec2 size_ac = texture->size;
    float ratio = texture->size.x / texture->size.y;

    size_ac = vec2_divs(size_ac, texture->size.y);
    size_ac.x /= _ui.ratiowh;
    ui_draw_full_rel(texture, pos, vec2_muls(size_ac, ratio * size));
}

void ui_draw_y(texture2 *texture, vec2 pos, float size)
{
    vec2 size_ac = texture->size;

    size_ac = vec2_divs(size_ac, texture->size.y);
    size_ac.x /= _ui.ratiowh;
    ui_draw_full_rel(texture, pos, vec2_muls(size_ac, size));
}

void ui_display(int task, demo_t *demo)
{
    (void)task;
    (void)demo;
    glUseProgram(_ui.ui_program);
    ui_draw_full_rel(_ui.tex, (vec2){-1.0f, 1.0f - 0.25f},
    (vec2){0.15f, 0.25f});
    ui_draw_full_rel(_ui.tex, (vec2){-0.85f, 1.0f - 0.25f},
    (vec2){0.05f, 0.25f});
    ui_draw_full_rel(_ui.tex, (vec2){-0.90f, 0.975f - 0.20f},
    (vec2){0.75f, 0.20f});
    ui_draw_x(_ui.tex, (vec2){-1.0f, -1.0f}, 0.25f);
}
