/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** quest_at_check
*/

#include "headers.h"

static int check_at_lvl(vg_quest *src)
{
    entity3_tag_player_data_t *data = _demo->world.player->tag_data;

    if (data->level >= src->lvl) {
        src->did = 1;
        for (int i = 0; i < src->nb_loot; i++)
            invent_add_item(src->loot);
        src->next_step();
        return 1;
    }
    return 0;
}

static int check_at_kill(vg_quest *src)
{
    entity3_tag_player_data_t  *data = _demo->world.player->tag_data;

    switch (src->enemy_to_kill) {
    case ENEMY_FISH:
        if (_demo->quest.fish_killed >= src->nb_to_kill) {
            _demo->quest.fish_killed = 0;
            for (int i = 0; i < src->nb_loot; i++)
                invent_add_item(src->loot);
            data->xp += src->xp_looted;
            src->next_step();
            return 1;
        }
        return 0;
    case ENEMY_BASE:
        if (_demo->quest.fish_killed >= src->nb_to_kill) {
            _demo->quest.fish_killed = 0;
            for (int i = 0; i < src->nb_loot; i++)
                invent_add_item(src->loot);
            data->xp += src->xp_looted;
            src->next_step();
            return 1;
        }
        return 0;
    default:
        return 0;
    }
}

static int check_at_loot(vg_quest *src)
{
    entity3_tag_player_data_t  *data = _demo->world.player->tag_data;

    for (int i = 0; i < INVENTORY_SIZE; i++) {
        if (_iu.invent.inventory[i].item == src->item_to_loot
        &&  _iu.invent.inventory[i].nb == src->nb) {
            for (int i = 0; i < src->nb_loot; i++)
                invent_add_item(src->loot);
            data->xp += src->xp_looted;
            src->next_step();
            return 1;
        }
    }
    return 0;
}

int quest_check_success(quests_list_t index)
{
    switch (_demo->quest.quest[index].at) {
    case AT_LVL:
        return check_at_lvl(&_demo->quest.quest[index]);
    case AT_LOOT:
        return check_at_loot(&_demo->quest.quest[index]);
    case AT_KILL:
        return check_at_kill(&_demo->quest.quest[index]);
    default:
        return 0;
    }
}