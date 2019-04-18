/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** font
*/

#include "headers.h"

void iu_set_font(void)
{
    _iu.fonts[FONT_MINECRAFT] = (font_t){IUTEX_FONT_MINECRAFT, 16, 16};
}

void iu_draw_font(entity2_param_t canvas, vec2 tex_pos, vec2 tex_size)
{
    gluint pos = glGetUniformLocation(_demo->shader[SHADER_FONT], "tex_pos");
    gluint size = glGetUniformLocation(_demo->shader[SHADER_FONT], "tex_size");
    gluint pos_id = glGetUniformLocation(_demo->shader[SHADER_FONT], "pos");
    gluint size_id = glGetUniformLocation(_demo->shader[SHADER_FONT], "size");
    gluint depth_id = glGetUniformLocation(_demo->shader[SHADER_FONT], "depth");

    glUniform1f(depth_id, canvas.depth);
    glUniform2fv(pos_id, 1, (glfloat *)&canvas.rect.p);
    glUniform2fv(size_id, 1, (glfloat *)&canvas.rect.s);
    glUniform2fv(pos, 1, (glfloat *)&tex_pos);
    glUniform2fv(size, 1, (glfloat *)&tex_size);
    glBindBuffer(GL_ARRAY_BUFFER, _iu.data.vertex_buffer);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
    sizeof(vec2), BUFFER_OFFSET(0));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _iu.textures[canvas.index]->id);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(0);
}

void iu_display_str(char *str_to_display, rect_t pos, font_list_t index)
{
    glUseProgram(_demo->shader[SHADER_FONT]);
    iu_draw_font((entity2_param_t){_iu.fonts[index].index,
    (rect_t){{pos.p.x, pos.p.y}, {pos.s.x, pos.s.y}}, -0.999},
    (vec2){8.0f, 1.0f},
    (vec2){1.0f / 16.0f , 1.0f / 16.0f});
}