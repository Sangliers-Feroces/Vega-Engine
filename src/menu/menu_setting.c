/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** menu_setting
*/

#include "headers.h"

void setting_draw(menu_t *menu)
{
    iu_entity_draw(menu->background[MENU_BG_SETTING]);
}

void menu_setting_loop(demo_t *demo, menu_t *menu)
{
    while (menu_poll_events(demo, menu)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(_iu.data.iu_program);
        menu_draw(menu);
        setting_draw(menu);
        sfRenderWindow_display(demo->win.window);
    }
}