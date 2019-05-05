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

    _demo->quest.enemy_killed[enemy_data->enemy_type]++;
}

void main_quest_start(void)
{
    _iu.current_dialogue =
    _demo->quest.quest[_demo->quest.curr_main_quest].first_dial;
}
