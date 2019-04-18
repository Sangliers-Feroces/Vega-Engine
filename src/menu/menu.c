/*
** EPITECH PROJECT, 2019
** MUL_my_world_2018
** File description:
** menu
*/

#include "headers.h"

void menu_quit(menu_t *menu)
{
    for (int i = 0; i < SETTING_END; i++)
        if (menu->setting[i].pattern == PATTERN_SLIDE_BUTTON)
            free(menu->setting[i].slider);
    sfMusic_destroy(menu->music);
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
