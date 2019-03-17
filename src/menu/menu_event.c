/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** menu_event
*/

#include "headers.h"

static void set_cursor(menu_t *menu)
{
    switch (menu->menu_state) {
        case 0:
            menu->object[MENUOBJECT_CURSOR].pos = (vec2){-0.30f, -0.23f};
            break;
        case 1:
            menu->object[MENUOBJECT_CURSOR].pos = (vec2){-0.30f, -0.43f};
            break;
    }
}

static void poll_arrow_pos(menu_t *menu)
{
    if (sfKeyboard_isKeyPressed(sfKeyUp)) {
        sfSound_play(menu->move);
        if (menu->menu_state <= 1 && menu->menu_state > 0)
            menu->menu_state--;
    }
    while (sfKeyboard_isKeyPressed(sfKeyUp));
    if (sfKeyboard_isKeyPressed(sfKeyDown)) {
        sfSound_play(menu->move);
        if (menu->menu_state >= 0 && menu->menu_state < 1)
            menu->menu_state++;
        
    }
    while (sfKeyboard_isKeyPressed(sfKeyDown));
    set_cursor(menu);
}

int menu_poll_events(demo_t *demo, menu_t *menu)
{
    menu->last_return = menu->cur_return;
    menu->cur_return = sfKeyboard_isKeyPressed(sfKeyEnter);
    if (menu->last_return && (!menu->cur_return)) {
        sfSound_play(menu->select);
        if (!menu->intro_state) {
            menu->skip_intro = 1;
            menu->intro_state = 1;
        }
        else
            return 0;
    }
    poll_arrow_pos(menu);
    if (!poll_events(demo)) {
        menu->intro_state = 0;
        menu->menu_state = 2;
        return 0;
    }
    return 1;
}
