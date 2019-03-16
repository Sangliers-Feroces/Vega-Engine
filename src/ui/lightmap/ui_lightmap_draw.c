/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** ui_lightmap_draw
*/

#include "headers.h"

void ui_lm_draw_full_rel(uilightmap_t index, rect_t rect, float depth)
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
    glBindTexture(GL_TEXTURE_2D, _ui.ui_lightmap_struct.textures[index]->id);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(0);
}

void ui_lightmap_draw_background(button_t bg)
{
    ui_lm_draw_full_rel(bg.texture_index, button_get_size(bg), bg.depth);
}