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
        if (menu->menu_choice == 4)
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

int menu_poll_events(demo_t *demo, menu_t *menu)
{
    if (!demo_poll_events(demo))
        return 0;
    if (_demo->input.key_press[KEY_ENTER]) {
        menu->state = menu->menu_choice;
        return 0;
    }
    analyse_move_menu(menu);
    return 1;
}
