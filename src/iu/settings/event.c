/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** event
*/

#include "headers.h"

int setting_poll_event(void)
{
    if (!demo_poll_events(_demo))
        return 0;
    if (_demo->input.key_press[KEY_ESC])
        return 0;
    return 1;
}