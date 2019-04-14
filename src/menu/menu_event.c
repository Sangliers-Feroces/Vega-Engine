/*
** EPITECH PROJECT, 2019
** MUL_my_world_2018
** File description:
** menu_event
*/

#include "headers.h"

void analyse_move_menu(menu_t *menu)
{
    if (sfKeyboard_isKeyPressed(sfKeyDown)) {
        if (menu->menu_choice == 5)
            return;
        if (menu->first_save == 1 && menu->menu_choice + 1 == 2)
            menu->menu_choice++;
        menu->menu_choice++;
        while (sfKeyboard_isKeyPressed(sfKeyDown));
    }
    if (sfKeyboard_isKeyPressed(sfKeyUp)) {
        if (menu->menu_choice == menu->first_save)
            return;
        if (menu->first_save == 1 && menu->menu_choice - 1 == 2)
            menu->menu_choice--;
        menu->menu_choice--;
        while (sfKeyboard_isKeyPressed(sfKeyUp));
    }
}

int analyse_input(demo_t *demo, menu_t *menu)
{
    switch (menu->branch) {
        case MENU_BRANCH_ROOT:
            analyse_move_menu(menu);
            break;
        case MENU_BRANCH_SETTING:
            if (demo->mouse.button_click)
                analyse_setting_input(demo, menu);
            break;
        default:
            break;
    }
    return 1;
}

int menu_poll_events(demo_t *demo, menu_t *menu)
{
    if (!poll_events(demo))
        return 0;
    if (sfKeyboard_isKeyPressed(sfKeyEnter))
        menu->state = menu->menu_choice;
    if (sfKeyboard_isKeyPressed(sfKeyEscape) &&
    menu->branch == MENU_BRANCH_SETTING)
        return 0;
    analyse_input(demo, menu);
    return 1;
}
