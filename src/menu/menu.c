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
    menu->music = sfMusic_createFromFile("res/musics/main_music.ogg");
    sfMusic_play(menu->music);
    menu->choosen_res = LIST_RES_1600_900;
    menu->edited_setting = 0;
    menu->first_save = 0;
    menu->state = -1;
    menu->branch = MENU_BRANCH_ROOT;
    menu->menu_choice = menu->first_save;
    menu_set_entities(menu);
}

void menu_quit(menu_t *menu)
{
    for (int i = 0; i < SETTING_END; i++)
        if (menu->setting[i].pattern == PATTERN_SLIDE_BUTTON)
            free(menu->setting[i].slider);
    sfMusic_destroy(menu->music);
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
