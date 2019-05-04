/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** quest_init
*/

#include "headers.h"

static void set_quest(void)
{
    _demo->quest.quest[MAIN_QUEST_1] = vg_quest_create(DIALOGUE_MAIN1_START
    , AT_LVL, &vg_next_mq);
    vg_quest_set_at_params(&_demo->quest.quest[MAIN_QUEST_1],
    0, 0, 0, 2);
    vg_quest_set_loot(&_demo->quest.quest[MAIN_QUEST_1],
    ITEM_APPLE, 5, 10);
    _demo->quest.quest[MAIN_QUEST_2] = vg_quest_create(DIALOGUE_MAIN2_START
    , AT_LVL, &vg_end_storie);
    vg_quest_set_at_params(&_demo->quest.quest[MAIN_QUEST_2],
    0, 0, 0, 3);
    vg_quest_set_loot(&_demo->quest.quest[MAIN_QUEST_2],
    ITEM_BOAT, 1, 10);
}

void quest_init(void)
{
    _demo->quest.curr_main_quest = MAIN_QUEST_1;
    set_quest_dialogues();
    set_quest();
}