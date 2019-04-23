/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** dialogue_fucntions_ptr
*/

#include "headers.h"

void vg_effect_no_effect(void)
{
    return;
}

void vg_effect_quit(void)
{
    sfRenderWindow_close(_demo->win.window);
}