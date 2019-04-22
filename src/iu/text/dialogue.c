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

void iu_text_init(void)
{
    for (int i = 0; i < TEXT_END; i++)
        _iu.text_src[i] = NULL;
    for (int i = 0; text_array[i].src != NULL; i++)
        _iu.text_src[text_array[i].index] =
        text_array[i].src;
    _iu.current_dialogue = DIALOGUE_END;
}

void iu_set_dialogue(void)
{
    _iu.dialogue_list[DIALOGUE_WELCOME] = vg_dialogue_create(2, TEXT_TEST);
    vg_dialogue_set_cadre(&_iu.dialogue_list[DIALOGUE_WELCOME], IUCADRE_BLACK);
    vg_dialogue_set_position(&_iu.dialogue_list[DIALOGUE_WELCOME],
    (vec2){-0.5f, -0.80f});
}
