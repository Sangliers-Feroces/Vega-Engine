/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** settings_loop
*/

#include "headers.h"

static void setting_draw(void)
{
    for (int i = 0; i < SETTINGS_END; i++) {
        iu_entity_draw(_iu.settings.entities[i]);
    }
    //iu_entity_draw(_iu.settings.entities[SETTINGS_BG]);
}

void setting_loop(void)
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        setting_draw();
        sfRenderWindow_display(_demo->win.window);
    } while (setting_poll_event());
}