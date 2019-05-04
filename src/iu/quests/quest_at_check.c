/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** quest_at_check
*/

#include "headers.h"

static int check_at_lvl(vg_quest *src)
{
    //printf("player lvl : %d, expected : %d\n", _demo->player.lvl, src->lvl);
    if (_demo->player.lvl >= src->lvl) {
        //printf("oui!!!\n");
        src->did = 1;
        //add xp;
        for (int i = 0; i < src->nb_loot; i++)
            invent_add_item(src->loot);
        src->next_step();
        return 1;
    }
    return 0;
}

int quest_check_success(quests_list_t index)
{
    switch (_demo->quest.quest[index].at) {
    case AT_LVL:
        return check_at_lvl(&_demo->quest.quest[index]);
    default:
        return 0;
    }
}