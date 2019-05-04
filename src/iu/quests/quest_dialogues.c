/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** quest_dialogues
*/

#include "headers.h"

void set_quest_dialogues(void)
{
    _iu.dialogue_list[DIALOGUE_MAIN1_START] = vg_dialogue_create(4,
    TEXT_MAIN1_START1);
    vg_dialogue_set_choices(&_iu.dialogue_list[DIALOGUE_MAIN1_START],
    "(A) : Accept", "(E) : Accept", &vg_no_effect, &vg_no_effect);
    _iu.dialogue_list[DIALOGUE_MAIN2_START] = vg_dialogue_create(1,
    TEXT_MAIN2_START1);
    _iu.dialogue_list[DIALOGUE_END_STORIE] = vg_dialogue_create(3,
    TEXT_END_1);
    vg_dialogue_set_choices(&_iu.dialogue_list[DIALOGUE_END_STORIE],
    "(A) : Stay", "(E) : Leave", &vg_no_effect, &vg_effect_quit);
}