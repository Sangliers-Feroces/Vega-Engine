/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** demo_time
*/

#include "headers.h"

static double clocks_get_eleapsed_time_second(void)
{
    sfTime result = sfClock_getElapsedTime(_demo->clocks.game_clock);

    return (result.microseconds / 1000000.0);
}

void clocks_refresh_time(void)
{
    _demo->clocks.t = clocks_get_eleapsed_time_second();
}

void clocks_init(demo_t *demo)
{
    demo->clocks.game_clock = sfClock_create();
}

void clocks_quit(demo_t *demo)
{
    sfClock_destroy(demo->clocks.game_clock);
}
