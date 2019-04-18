/*
** EPITECH PROJECT, 2019
** MUL_my_world_2018
** File description:
** menu_init
*/

#include "headers.h"

void menu_init(menu_t *menu)
{
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
