/*
** EPITECH PROJECT, 2019
** MUL_my_world_2018
** File description:
** menu_init
*/

#include "headers.h"

void menu_init(menu_t *menu)
{
    menu->edited_setting = 0;
    menu->first_save = 0;
    menu->state = -1;
    menu->branch = MENU_BRANCH_ROOT;
    menu->menu_choice = menu->first_save;
    menu_set_entities(menu);
}
