/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** setting_effect
*/

#include "headers.h"

void setting_buttons_effects(demo_t *demo, menu_t *menu, setting_entity_t choice)
{
    (void)demo;
    switch (choice) {
        case SETTING_RES_MINUS:
            if (menu->setting[SETTING_RES_CHOICE].index > IUTEX_SETTING_RES_1600_900) {
                menu->setting[SETTING_RES_CHOICE].index--;
                menu->edited_setting = 1;
            }
            return;
        case SETTING_RES_PLUS:
            if (menu->setting[SETTING_RES_CHOICE].index < IUTEX_SETTING_RES_1920_1080) {
                menu->setting[SETTING_RES_CHOICE].index++;
                menu->edited_setting = 1;
            }
            return;
        default:
            return;
    }
}

int analyse_setting_input(demo_t *demo, menu_t *menu)
{
    for (int i = 0; i < SETTING_END; i++) {
        if (check_click_pos(sfMouse_getPosition((sfWindow *)demo->win.window),
        menu->setting[i], demo->win.w, demo->win.h)) {
            setting_buttons_effects(demo, menu, SETTING_RES + i);
        }
    }
    return 1;
}
