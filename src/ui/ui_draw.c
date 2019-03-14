/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** ui
*/

#include "headers.h"

void ui_draw_full_rel(uires_t index, vec2 pos, vec2 size)
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
    glBindTexture(GL_TEXTURE_2D, _ui.textures[index]->id);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(0);
}

void ui_draw_x(uires_t index, vec2 pos, float size)
{
    vec2 size_ac = _ui.textures[index]->size;
    float ratio = _ui.textures[index]->size.x / _ui.textures[index]->size.y;

    size_ac = vec2_divs(size_ac, _ui.textures[index]->size.y);
    size_ac.x /= ratio;
    size_ac.y *= _ui.ratiowh / ratio;
    ui_draw_full_rel(index, pos, vec2_muls(size_ac, size));
}

void ui_draw_y(uires_t index, vec2 pos, float size)
{
    vec2 size_ac = _ui.textures[index]->size;

    size_ac = vec2_divs(size_ac, _ui.textures[index]->size.y);
    size_ac.x /= _ui.ratiowh;
    ui_draw_full_rel(index, pos, vec2_muls(size_ac, size));
}

void ui_display(int task, demo_t *demo)
{
    (void)task;
    (void)demo;
    glUseProgram(_ui.ui_program);
    for (int i = 0; i < UIBUTTON_MAX; i++)   {
        ui_draw_x(_ui.buttons[i].texture_index, _ui.buttons[i].pos, _ui.buttons[i].size);
    }
}
