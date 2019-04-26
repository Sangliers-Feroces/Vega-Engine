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

typedef struct {
    char *name;
    items_type_t type;
    iutex_t texture;
    //if wepaons
    int attack;
    //if consumable
    int restored_hp;
    int restored_mana;
} item_data_t;

typedef struct {
    entity2_t item_image;
    vg_text invent_items_name[5];
    item_data_t items_list[ITEM_END];
} invent_t;
