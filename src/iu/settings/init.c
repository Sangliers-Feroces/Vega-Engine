/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** init
*/

#include "headers.h"

void settings_init(void)
{
    _iu.settings.hints_state = WITH_HINT;
    _iu.settings.screen_state = FULLSCREEN;
    setting_set_entities();
}