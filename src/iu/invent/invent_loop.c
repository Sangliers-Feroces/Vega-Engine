/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** invent_loop
*/

#include "headers.h"

static int invent_poll_event(void)
{
    if (!poll_events(_demo))
        return 0;
    if (_demo->input.key_press[KEY_TAB] || _demo->input.key_press[KEY_ESC])
        return 0;
    return 1;
}

static void draw_invent(void)
{
    world_render();
    glUseProgram(_demo->shader[SHADER_IU].program);
    for (int i = 0; i < IUINVENT_END; i++)
            iu_entity_draw(_iu.invent_bg[i]);
        iu_entity_draw(_iu.invent.item_image);
        for (int i = 0; i < 5; i++)
            vg_text_draw(_iu.invent.invent_items_name[i]);
}

void invent_loop(void)
{
    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        draw_invent();
        sfRenderWindow_display(_demo->win.window);
    } while (invent_poll_event());
    _iu.data.is_invent = !_iu.data.is_invent;
}