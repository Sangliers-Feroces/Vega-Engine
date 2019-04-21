/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** dialogue
*/

#include "headers.h"

const text_src_t text_array[] = {
    {TEXT_TEST, "Gretting you sick fucker and welcome in the sabondi's island"},
    {TEXT_TEST_2, "On as censuré mon géni"},
    {0, NULL}
};

void display_str_temp(char *str, rect_t start, font_list_t font)
{
    glUseProgram(_demo->shader[SHADER_FONT]);
    glBindVertexArray(_iu.data.vertex_array);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _iu.textures[_iu.fonts[font].index]->id);
    for (int i = 0; str[i] != '\0'; i++) {
        iu_display_char(str[i], start, font);
        start.p.x += start.s.x;
    }
}

void iu_text_set_grp(void)
{
    _iu.text_grp[TEXT_GRP_IND_WELCOME] = (text_grp_t) {2, 2, TEXT_TEST, 0};
}

void iu_text_init(void)
{
    for (int i = 0; i < TEXT_END; i++)
        _iu.text[i] = NULL;
    for (int i = 0; text_array[i].src != NULL; i++)
        _iu.text[text_array[i].index] =
        text_array[i].src;
    iu_text_set_grp();
}
