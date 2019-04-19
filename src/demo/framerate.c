/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

void demo_update_framerate(demo_t *demo)
{
    static size_t frame = 0;
    size_t stride = 4;

    frame++;
    if (frame >= stride) {
        demo->win.framelen =
        sfTime_asSeconds(sfClock_getElapsedTime(demo->win.frametime)) /
        (float)stride;
        sfClock_restart(demo->win.frametime);
        frame = 0;
        //printf("%f FPS\n", 1.0 / demo->win.framelen);
    }
}
