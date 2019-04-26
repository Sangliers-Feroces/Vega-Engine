/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** demo_time
*/

#include "headers.h"

float get_eleapsed_time_second(sfClock *clock_)
{
    sfTime result = sfClock_getElapsedTime(clock_);

    return (result.microseconds / 1000000.0);
}

void clocks_init(demo_t *demo)
{
    demo->clocks.game_clock = sfClock_create();
}

void clocks_quit(demo_t *demo)
{
    sfClock_destroy(demo->clocks.game_clock);
}