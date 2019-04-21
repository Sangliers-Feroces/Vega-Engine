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
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void iu_display_char(char c, rect_t pos, font_list_t index)
{
    float offset_x = 1.0f / _iu.fonts[index].cols;
    float offset_y = 1.0f / _iu.fonts[index].lines;
    float char_x_pos = c % _iu.fonts[index].cols;
    float char_y_pos = (c / _iu.fonts[index].lines) + 1.0f;

    iu_draw_font((entity2_param_t){_iu.fonts[index].index,
    (rect_t){{pos.p.x, pos.p.y}, {pos.s.x, pos.s.y}}, -0.999},
    (vec2){char_x_pos * offset_x, char_y_pos * offset_y},
    (vec2){offset_x, offset_y});
}
