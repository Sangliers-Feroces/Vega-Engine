/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** ui
*/

#include "headers.h"

void ui_draw_full_rel(int index, rect_t rect, float depth)
{
    gluint pos_id = glGetUniformLocation(_ui.ui_program, "pos");
    gluint size_id = glGetUniformLocation(_ui.ui_program, "size");
    gluint depth_id = glGetUniformLocation(_ui.ui_program, "depth");

    glUniform1f(depth_id, depth);
    glUniform2fv(pos_id, 1, (glfloat *)&rect.p);
    glUniform2fv(size_id, 1, (glfloat *)&rect.s);
    glBindBuffer(GL_ARRAY_BUFFER, _ui.vertex_buffer);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
    sizeof(vec2), BUFFER_OFFSET(0));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _ui.textures[index]->id);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(0);
}

void button_draw(button_t button)
{
    ui_draw_full_rel(button.texture_index, button_get_size(button),
    button.depth);
}

void ui_display(int task, demo_t *demo)
{
    (void)task;
    (void)demo;
    glUseProgram(_ui.ui_program);
    for (int i = 0; i < UIBUTTON_MAX; i++) {
        button_draw(_ui.buttons[i]);
    }
    display_selected_texture(demo, -1.0f);
}
