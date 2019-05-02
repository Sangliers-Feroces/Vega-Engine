/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** items_constructor
*/

#include "headers.h"

static void invent_set_items(void)
{
    _iu.invent.items_list[ITEM_SWORD_1] = (item_data_t){"l'epee batarde",
    TYPE_CAC, IUTEX_ITEM_SWORD1, 20, 0, 0, 0};
    _iu.invent.items_list[ITEM_SWORD_2] = (item_data_t){"l'epee Gauldur",
    TYPE_CAC, IUTEX_ITEM_SWORD2, 30, 0, 0, 0};
    _iu.invent.items_list[ITEM_SWORD_3] = (item_data_t){
    "Dard du Penitus Oculatus", TYPE_CAC, IUTEX_ITEM_SWORD3, 40, 0, 0, 0};
    _iu.invent.items_list[ITEM_APPLE] = (item_data_t){"Mac Crunch",
    TYPE_CONSUMABLE, IUTEX_ITEM_APPLE, 0, 5, 0, 0};
    _iu.invent.items_list[ITEM_BOAT] = (item_data_t){"Shit Stormer",
    TYPE_VEHICULE, IUTEX_ITEM_BOAT, 0, 0, 0, 90};
    _iu.invent.items_list[ITEM_BOW] = (item_data_t){"L'ocean atlantique"
    "est un mythe", TYPE_DISTANCE, IUTEX_ELON, 1000, 0, 0, 0};
    _iu.invent.items_list[ITEM_PLANE] = (item_data_t){"Je prefere "
    "pas faire de blague la", TYPE_VEHICULE, IUTEX_ELON, 0, 0, 0, 200};
}

static void set_desc(void)
{
    _iu.invent.desc_name = vg_text_create(NULL, NULL);
    vg_text_set_position(&_iu.invent.desc_name, (vec2){0.05f, 0.15f});
    _iu.invent.desc_type = vg_text_create(NULL, NULL);
    vg_text_set_position(&_iu.invent.desc_type, (vec2){0.05f, 0.05f});
    _iu.invent.desc_value = vg_text_create(NULL, NULL);
    vg_text_set_position(&_iu.invent.desc_value, (vec2){0.05f, -0.05f});
    vg_text_set_size(&_iu.invent.desc_name, (vec2){0.02f, 0.03f});
    vg_text_set_size(&_iu.invent.desc_type, (vec2){0.02f, 0.03f});
    vg_text_set_size(&_iu.invent.desc_value, (vec2){0.02f, 0.03f});
}

void invent_init(void)
{
    invent_set_items();
    _iu.invent.text_start = 0;
    _iu.invent.index_cursor = 0;
    _iu.invent.focused_item = 0;
    _iu.invent.save_focus = 0;
    _iu.invent.equiped_state = 0;
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        _iu.invent.inventory[i].item = NO_ITEM;
        _iu.invent.inventory[i].nb = 0;
    }
    for (int i = 0; i < 5; i++) {
        _iu.invent.invent_items_name[i] = vg_text_create(NULL, NULL);
        vg_text_set_position(&_iu.invent.invent_items_name[i],
        (vec2){-0.08f, -0.25f - (i * 0.08f)});
        vg_text_reset_str(&_iu.invent.invent_items_name[i], "Empty", NULL);
    }
    set_desc();
    invent_stat_display_init();
}