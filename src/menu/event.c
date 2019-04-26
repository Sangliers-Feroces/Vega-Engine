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
            if (demo->mouse.button_state)
                analyse_setting_input(demo, menu);
            break;
        default:
            break;
    }
    return 1;
}

int wait_confirmation(demo_t *demo, menu_t *menu)
{
    int check_input = 0;
    int state = 0;

    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(_demo->shader[SHADER_IU].program);
        menu_draw(menu);
        setting_draw(menu);
        iu_entity_draw(menu->confirmation);
        sfRenderWindow_display(demo->win.window);
        if (sfKeyboard_isKeyPressed(sfKeySpace)) {
            state = 0;
            check_input++;
            menu->edited_setting = 0;
        }
        else if (sfKeyboard_isKeyPressed(sfKeyEnter)) {
            state = 1;
            check_input++;
        }
    } while (demo_poll_events(demo) && !check_input);
    return state;
}

int menu_poll_events(demo_t *demo, menu_t *menu)
{
    if (!demo_poll_events(demo)) {
        menu->edited_setting = 0;
        return 0;
    }
    if (sfKeyboard_isKeyPressed(sfKeyEnter))
        menu->state = menu->menu_choice;
    if (sfKeyboard_isKeyPressed(sfKeyEscape) &&
    menu->branch == MENU_BRANCH_SETTING) {
        if (menu->edited_setting == 1)
            return wait_confirmation(demo, menu);
        return 0;
    }
    analyse_input(demo, menu);
    return 1;
}
