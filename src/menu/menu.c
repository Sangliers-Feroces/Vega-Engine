/*
** EPITECH PROJECT, 2019
** MUL_my_world_2018
** File description:
** menu
*/

#include "headers.h"

void menu_init(menu_t *menu)
{
    _iu.data.is_focus = 1;
    demo_update_cursor_visibility(_demo);
    menu->edited_setting = 0;
    menu->first_save = 0;
    menu->state = -1;
    menu->branch = MENU_BRANCH_ROOT;
    menu->menu_choice = menu->first_save;
    menu_set_entities(menu);
}

void menu_quit(menu_t *menu)
{
    _iu.data.is_focus = 0;
}

int start(demo_t *demo)
{
    menu_t menu;

    menu_init(&menu);
    /*if (demo->skip_intro)
        if (!intro(demo))
            return 0;*/
    if (!menu_loop(demo, &menu)) {
        menu_quit(&menu);
        return 0;
    }
    menu_quit(&menu);
    return 1;
}
