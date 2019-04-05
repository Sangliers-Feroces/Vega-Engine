/*
** EPITECH PROJECT, 2019
** MUL_my_world_2018
** File description:
** menu
*/

#include "headers.h"

int start(demo_t *demo)
{
    menu_t menu;

    menu_init(&menu);
    /*if (demo->skip_intro)
        if (!intro(demo))
            return 0;*/
    printf("attend quoi\n");
    if (!menu_loop(demo, &menu))
        return 0;
    return 1;
}