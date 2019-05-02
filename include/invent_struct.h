/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** invent_struct
*/

#pragma once

typedef enum {
    ITEM_SWORD_1,
    ITEM_SWORD_2,
    ITEM_SWORD_3,
    ITEM_APPLE,
    ITEM_BOAT,
    ITEM_PLANE,
    ITEM_BOW,
    ITEM_END,
    NO_ITEM
} items_t;

typedef enum {
    TYPE_CONSUMABLE,
    TYPE_CAC,
    TYPE_DISTANCE,
    TYPE_VEHICULE
} items_type_t;

typedef enum {
    INVENT_BUTTON_EQUIP,
    INVENT_BUTTON_DROP,
    INVENT_BUTTON_END
} invent_buuttons_t;

typedef enum {
    STAT_HP,
    STAT_MANA,
    STAT_ATTACK,
    STAT_DEFENSE,
    STAT_LVL,
    STAT_XP,
    STAT_END
} stat_display_t;

typedef struct {
    char *name;
    items_type_t type;
    iutex_t texture;
    //if wepaons
    int attack;
    //if consumable
    int restored_hp;
    int restored_mana;
    //if vheicule
    int speed;
} item_data_t;

typedef struct {
    int text_start;
    int index_cursor;
    int focused_item;
    //
    entity2_t item_image;
    entity2_t cursor;
    vg_text invent_items_name[5];
    items_t *inventory;
    item_data_t items_list[ITEM_END];
    //desc
    vg_text desc_name;
    vg_text desc_type;
    vg_text desc_value;
    //button's array
    vg_text stats[STAT_END];
    entity2_t buttons[INVENT_BUTTON_END];
} invent_t;
