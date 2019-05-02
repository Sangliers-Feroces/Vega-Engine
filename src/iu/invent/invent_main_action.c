/*
** EPITECH PROJECT, 2019
** h
** File description:
** invent_main_action
*/

#include "headers.h"

void invent_refresh_attack_added(void)
{
    if (_iu.invent.inventory[10].item == NO_ITEM)
        _demo->player.attack_add = 0;
    else
        _demo->player.attack_add =
        _iu.invent.items_list[_iu.invent.inventory[10].item].attack;
}

static void invent_equip(void)
{
    items_t save;

    if (_demo->input.key_press[KEY_ENTER]) {
        save = _iu.invent.inventory[_iu.invent.focused_item].item;
        if (_iu.invent.inventory[10].item != NO_ITEM)
            _iu.invent.inventory[_iu.invent.focused_item].item =
            _iu.invent.inventory[10].item;
        else
            _iu.invent.inventory[_iu.invent.focused_item].item = NO_ITEM;
        _iu.invent.inventory[10].item = save;
    }
}

static void invent_consume(void)
{
    _demo->player.curr_hp += _iu.invent.items_list[
    _iu.invent.inventory[_iu.invent.focused_item].item].restored_hp;
    if (_demo->player.curr_hp > _demo->player.hp)
        _demo->player.curr_hp -= (_demo->player.curr_hp - _demo->player.hp);
    _iu.invent.inventory[_iu.invent.focused_item].nb--;
    if (!_iu.invent.inventory[_iu.invent.focused_item].nb)
        _iu.invent.inventory[_iu.invent.focused_item].item = NO_ITEM;
    return;
}

void invent_switch_action(void)
{
    if (_iu.invent.inventory[_iu.invent.focused_item].item == NO_ITEM) {
        invent_equip();
        return;
    }
    switch (_iu.invent.items_list[_iu.invent.inventory[
        _iu.invent.focused_item].item].type) {
        case TYPE_CAC:
            return invent_equip();
        case TYPE_DISTANCE:
            return;
        case TYPE_CONSUMABLE:
            return invent_consume();
        case TYPE_VEHICULE:
            return;
        default:
            return;
    }
}