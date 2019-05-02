/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** invent_loop
*/

#include "headers.h"

static void reset_str_invent(int text_start)
{
    for (int i = 0; i < 5; i++) {
        if (_iu.invent.inventory[text_start + i] == NO_ITEM)
            vg_text_reset_str(&_iu.invent.invent_items_name[i], "Empty", NULL);
        else
            vg_text_reset_str(&_iu.invent.invent_items_name[i],
            _iu.invent.items_list[_iu.invent.inventory[text_start + i]].name,
            NULL);
    }
}

static void desc_set_default(void)
{
    vg_text_reset_str(&_iu.invent.desc_name, "NAME:Neant Distordu",
    NULL);
    vg_text_reset_str(&_iu.invent.desc_type, "TYPE:No Type",
    NULL);
    vg_text_reset_str(&_iu.invent.desc_value, "VALUE:Over 9000",
    NULL);
}

static void invent_draw_desc(void)
{
    char buff_name[20];
    char buff_type[20];
    char buff_value[20];

    if (_iu.invent.inventory[_iu.invent.focused_item] == NO_ITEM)
        desc_set_default();
    else {
        sprintf(buff_name, "NAME:%s",
        _iu.invent.items_list[_iu.invent.inventory[_iu.invent.focused_item]].name);
        vg_text_reset_str(&_iu.invent.desc_name, buff_name, NULL);
        sprintf(buff_type, "TYPE:%s", invent_get_item_type());
        vg_text_reset_str(&_iu.invent.desc_type, buff_type, NULL);
        sprintf(buff_value, "%s%d", invent_get_item_value(),
        invent_get_item_data());
        vg_text_reset_str(&_iu.invent.desc_value, buff_value, NULL);
    }
    vg_text_draw(_iu.invent.desc_name);
    vg_text_draw(_iu.invent.desc_type);
    vg_text_draw(_iu.invent.desc_value);
}

static void draw_invent(void)
{
    world_render();
    glUseProgram(_demo->shader[SHADER_IU].program);
    for (int i = 0; i < IUINVENT_END; i++)
        iu_entity_draw(_iu.invent_bg[i]);
    invent_display_icon();
    iu_entity_draw(_iu.invent.cursor);
    for (int i = 0; i < 5; i++)
        vg_text_draw(_iu.invent.invent_items_name[i]);
    invent_draw_desc();
    invent_draw_stat();
}

void invent_loop(void)
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    do {
        reset_str_invent(_iu.invent.text_start);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        draw_invent();
        sfRenderWindow_display(_demo->win.window);
    } while (invent_poll_event());
    _iu.data.is_invent = !_iu.data.is_invent;
    _iu.invent.index_cursor = 0;
    _iu.invent.focused_item = 0;
}
