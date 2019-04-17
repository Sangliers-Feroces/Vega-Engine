/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** menu_setting
*/

#include "headers.h"

const resolutions_t list_resolutions[] = {
    {1600, 900, IUTEX_SETTING_RES_1600_900},
    {1920, 1080, IUTEX_SETTING_RES_1920_1080}
};

void setting_apply_changes(demo_t *demo,menu_t *menu)
{
    if (list_resolutions[menu->choosen_res].w != demo->win.w
    || list_resolutions[menu->choosen_res].h != demo->win.h) {
        demo->win.h = list_resolutions[menu->choosen_res].h;
        demo->win.w = list_resolutions[menu->choosen_res].w;
        sfRenderWindow_destroy(demo->win.window);
        demo->win.window = sfRenderWindow_create((sfVideoMode){demo->win.w,
        demo->win.h, 32}, "rtx on !", sfClose,
        &(sfContextSettings){24, 8, 4, 4, 3, 0, 1});
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

void setting_draw(menu_t *menu)
{
    iu_entity_draw(menu->background[MENU_BG_SETTING]);
    for (int i = 0; i < SETTING_END; i++) {
        iu_entity_draw(menu->setting[i]);
        if (menu->setting[i].pattern == PATTERN_SLIDE_BUTTON) {
            iu_entity_draw((*menu->setting[i].slider));
        }
    }
}

void menu_setting_loop(demo_t *demo, menu_t *menu)
{
    while (menu_poll_events(demo, menu)) {
        menu->setting[SETTING_RES_CHOICE].index = list_resolutions[menu->choosen_res].index;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(_iu.data.iu_program);
        menu_draw(menu);
        setting_draw(menu);
        sfRenderWindow_display(demo->win.window);
    }
}
