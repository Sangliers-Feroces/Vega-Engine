/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** menu_event
*/

#include "headers.h"

int menu_poll_events(demo_t *demo, menu_t *menu)
{
    if (sfKeyboard_isKeyPressed(sfKeyEnter))
        return 0;
    if (sfKeyboard_isKeyPressed(sfKeyDown)) {
        menu->object[MENUOBJECT_CURSOR].pos = (vec2){-0.40f, -0.67f};
        menu->menu_state = 0;
    }
    else if (sfKeyboard_isKeyPressed(sfKeyUp)) {
        menu->object[MENUOBJECT_CURSOR].pos = (vec2){-0.40f, -0.37f};
        menu->menu_state = 1;
    }
    if (sfKeyboard_isKeyPressed(sfKeySpace))
        menu->intro_state = 1;
    else if (sfKeyboard_isKeyPressed(sfKeyEscape)) {
        return 0;
    }
    if (!poll_events(demo))
        return (0);
    return (1);
}