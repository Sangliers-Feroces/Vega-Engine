/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** ui_texture
*/

#include "headers.h"

void display_selected_texture(demo_t *demo, float depth)
{
    gluint pos_id = glGetUniformLocation(_ui.ui_program, "pos");
    gluint size_id = glGetUniformLocation(_ui.ui_program, "size");
    gluint depth_id = glGetUniformLocation(_ui.ui_program, "depth");

    glUniform1f(depth_id, depth);
    glUniform2fv(pos_id, 1, (glfloat *)&(vec2){-0.435f, 0.75f});
    glUniform2fv(size_id, 1, (glfloat *)&(vec2){0.07f, 0.07f});
    glBindBuffer(GL_ARRAY_BUFFER, _ui.vertex_buffer);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
    sizeof(vec2), BUFFER_OFFSET(0));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,
    demo->texture_panel.texture[_ui.selected_texture]->id);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(0);
}
