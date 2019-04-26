/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** items_constructor
*/

#include "headers.h"

void invent_set_items(void)
{
    _iu.invent.items_list[ITEM_SWORD_1] = (item_data_t){"l'epee batarde",
    TYPE_CAC, IUTEX_ELON, 20, 0, 0};
    _iu.invent.items_list[ITEM_SWORD_2] = (item_data_t){"l'epee Gauldur",
    TYPE_CAC, IUTEX_ELON, 30, 0, 0};
    _iu.invent.items_list[ITEM_SWORD_3] = (item_data_t){
    "Dard du Penitus Oculatus", TYPE_CAC, IUTEX_ELON, 40, 0, 0};
    _iu.invent.items_list[ITEM_APPLE] = (item_data_t){"Mac Crunch",
    TYPE_CONSUMABLE, IUTEX_ELON, 0, 5, 0};
    _iu.invent.items_list[ITEM_BOAT] = (item_data_t){"Shit Stormer",
    TYPE_VEHICULE, IUTEX_ELON, 0, 0, 0};
    _iu.invent.items_list[ITEM_BOW] = (item_data_t){"L'ocean atlantique est un mythe",
    TYPE_DISTANCE, IUTEX_ELON, 1000, 0, 0};
    _iu.invent.items_list[ITEM_PLANE] = (item_data_t){"Je prefere pas faire de blague la",
    TYPE_VEHICULE, IUTEX_ELON, 0, 0, 0};
}

void invent_set_display_item_name(void)
{
    for (int i = 0; i < 5; i++) {
        _iu.invent.invent_items_name[i] = vg_text_create(NULL, NULL);
        vg_text_set_position(&_iu.invent.invent_items_name[i],
        (vec2){-0.15f, -0.25f - (i * 0.08f)});
    }
    vg_text_reset_str(&_iu.invent.invent_items_name[0],
    _iu.invent.items_list[0].name, NULL);
    vg_text_reset_str(&_iu.invent.invent_items_name[1],
    _iu.invent.items_list[1].name, NULL);
    vg_text_reset_str(&_iu.invent.invent_items_name[2],
    _iu.invent.items_list[2].name, NULL);
    vg_text_reset_str(&_iu.invent.invent_items_name[3],
    _iu.invent.items_list[3].name, NULL);
    vg_text_reset_str(&_iu.invent.invent_items_name[4],
    _iu.invent.items_list[4].name, NULL);
}