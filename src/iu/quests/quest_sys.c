/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** quest_sys
*/

#include "headers.h"

void quest_add_death_counter(entity3 *ent)
{
    entity3_tag_enemy_data_t *enemy_data = ent->tag_data;

    switch (enemy_data->enemy_type) {
    case ENEMY_FISH:
        _demo->quest.fish_killed++;
        break;
    case ENEMY_BASE:
        _demo->quest.base_killed++;
        break;
    default:
        return;
    }
    return;
}

void main_quest_start(void)
{
    _iu.current_dialogue =
    _demo->quest.quest[_demo->quest.curr_main_quest].first_dial;
}