/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** invent_loop
*/

#include "headers.h"

static void invent_inventory_list_draw(void)
{
    char buff_nb[5][64];

    for (int i = 0; i < 5; i++) {
        if (_iu.invent.inventory[_iu.invent.text_start + i].item == NO_ITEM)
            vg_text_reset_str(&_iu.invent.invent_items_name[i], "Empty", "");
        else if (_iu.invent.inventory[_iu.invent.text_start + i].nb == 1
        || _iu.invent.items_list[_iu.invent.inventory[
        _iu.invent.text_start + i].item].type == TYPE_CAC)
            vg_text_reset_str(&_iu.invent.invent_items_name[i],
            _iu.invent.items_list[_iu.invent.inventory[
            _iu.invent.text_start + i].item].name, NULL);
        else {
            sprintf(buff_nb[i], " x%d",
            _iu.invent.inventory[_iu.invent.text_start + i].nb);
            vg_text_reset_str(&_iu.invent.invent_items_name[i],
            _iu.invent.items_list[_iu.invent.inventory[
            _iu.invent.text_start + i].item].name, buff_nb[i]);
        }
    }
    for (int i = 0; i < 5; i++)
        vg_text_draw(_iu.invent.invent_items_name[i]);
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

    if (_iu.invent.inventory[_iu.invent.focused_item].item == NO_ITEM)
        desc_set_default();
    else {
        sprintf(buff_name, "NAME:%s",
        _iu.invent.items_list[_iu.invent.inventory
        [_iu.invent.focused_item].item].name);
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
    invent_inventory_list_draw();
    invent_display_icon();
    iu_entity_draw(_iu.invent.cursor);
    invent_draw_desc();
    invent_draw_stat();
}

static void update_world_weapon(void)
{
    entity3 *sword = _demo->world.player->sub.ent[0]->sub.ent[0]->sub.ent[0];
    switch (_iu.invent.inventory[10].item) {
    case ITEM_SWORD_1:
        entity3_set_render(sword, 0, mesh_full_ref_bank_init(MESH_BANK_SWORD),
        MATERIAL_GRASS);
        break;
    default:
        entity3_set_render(sword, 0, mesh_full_ref_get_null(),
        MATERIAL_GRASS);
        break;
    }
}

void invent_loop(void)
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        draw_invent();
        sfRenderWindow_display(_demo->win.window);
    } while (invent_poll_event());
    _iu.data.is_invent = !_iu.data.is_invent;
    _iu.invent.index_cursor = 0;
    _iu.invent.focused_item = 0;
    update_world_weapon();
}
