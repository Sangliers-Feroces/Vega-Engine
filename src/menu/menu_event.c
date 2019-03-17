/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** menu_event
*/

#include "headers.h"

static void poll_arrow_pos(menu_t *menu)
{
    if (sfKeyboard_isKeyPressed(sfKeyDown)) {
        menu->object[MENUOBJECT_CURSOR].pos = (vec2){-0.40f, -0.67f};
        menu->menu_state = 0;
    }
    else if (sfKeyboard_isKeyPressed(sfKeyUp)) {
        menu->object[MENUOBJECT_CURSOR].pos = (vec2){-0.40f, -0.37f};
        menu->menu_state = 1;
    }
}

int menu_poll_events(demo_t *demo, menu_t *menu)
{
    menu->last_return = menu->cur_return;
    menu->cur_return = sfKeyboard_isKeyPressed(sfKeyEnter);
    if (menu->last_return && (!menu->cur_return)) {
        if (!menu->intro_state)
            menu->intro_state = 1;
        else
            return 0;
    }
    poll_arrow_pos(menu);
    if (!poll_events(demo)) {
        menu->intro_state = 0;
        menu->menu_state = 0;
        return 0;
    }
    return 1;
}