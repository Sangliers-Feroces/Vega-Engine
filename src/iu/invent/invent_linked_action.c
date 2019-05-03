/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** invent_linked_action
*/

#include "headers.h"

int invent_add_item(items_t item)
{
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        if (_iu.invent.inventory[i].item == item) {
            _iu.invent.inventory[i].nb++;
            return 1;
        }
    }
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        if (_iu.invent.inventory[i].item == NO_ITEM) {
            _iu.invent.inventory[i].item = item;
            _iu.invent.inventory[i].nb = 1;
            return 1;
        }
    }
    vg_text_draw(_iu.data.error_message[ERROR_INVENT_FULL]);
    return 0;
    //display_error
}