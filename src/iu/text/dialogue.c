/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** dialogue
*/

#include "headers.h"

const text_src_t text_array[] = {
    {TEXT_TEST, "Welcome in the Vega World ! Here the world is a bit strange"},
    {TEXT_TEST_1, "You can't fight, you cant leave you're cuck ! GLHF to understand the equations behind these world"},
    {TEXT_TEST_2, "Do you want to kys ?"},
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
    _iu.dialogue_list[DIALOGUE_WELCOME] = vg_dialogue_create(3, TEXT_TEST);
    vg_dialogue_set_position(&_iu.dialogue_list[DIALOGUE_WELCOME],
    (vec2){-0.45f, -0.80f});
    vg_dialogue_set_choices(&_iu.dialogue_list[DIALOGUE_WELCOME],
    "(A) : Acepter", "(E) : Refuser", &vg_effect_quit, &vg_effect_no_effect);
    _iu.dialogue_list[DIALOGUE_WELCOME].choices = 1;
}
