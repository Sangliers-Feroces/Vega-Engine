/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** iu_constructor
*/

#include "headers.h"

void entity_set_new_rel(void)
{
    //add rell change here
    _iu.buttons[IUBUTTON_ELON].rel = IUREL_X;
}

void entity_set_new_pattern(void)
{
    //add pattern change here
    _iu.buttons[IUBUTTON_ELON].pattern = PATTERN_CLICK_BUTTON;
}

void entity_constructor(entity2_t *entity, entity2_param_t params)
{
    entity->index = params.index;
    entity->rect = params.rect;
    entity->depth = params.depth;
    entity->pattern = PATTERN_CLASSIC;
    entity->rel = IUREL_FULL;
}
