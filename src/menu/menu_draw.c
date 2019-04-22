/*
** EPITECH PROJECT, 2019
** MUL_my_world_2018
** File description:
** menu_draw
*/

#include "headers.h"

static void reset_cursor(menu_t *menu)
{
    menu->link[MENU_LINK_CURSOR].rect.p.y =
    (-0.30f + (menu->menu_choice * -0.1f));
}

void menu_draw(menu_t *menu)
{
    iu_entity_draw(menu->background[MENU_BG_MAIN]);
    for (int i = menu->first_save; i < MENU_LINK_END; i++)
        iu_entity_draw(menu->link[i]);
}

static int state_ananlyse(demo_t *demo, menu_t *menu)
{
    switch (menu->state) {
        case -1:
            return 0;
        case 5:
            return 0;
        case 3:
            menu->edited_setting = 0;
            menu->branch = MENU_BRANCH_SETTING;
            menu_setting_loop(demo, menu);
            if (menu->edited_setting == 1)
                setting_apply_changes(demo, menu);
            menu->branch = MENU_BRANCH_ROOT;
            menu->state = -1;
            return (menu_loop(demo, menu));
        default:
            return 1;
    };
}

int menu_loop(demo_t *demo, menu_t *menu)
{
    if (menu->first_save == 1)
        menu->link[MENU_LINK_LOAD].index = IUTEX_MENU_LOAD_FADE;
    else
        menu->link[MENU_LINK_LOAD].index = IUTEX_MENU_LOAD;
    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(_demo->shader[SHADER_IU].program);
        menu_draw(menu);
        sfRenderWindow_display(demo->win.window);
        reset_cursor(menu);
    } while (menu_poll_events(demo, menu) && menu->state == -1);
    return (state_ananlyse(demo, menu));
}
