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
    , AT_LOOT, &vg_next_mq);
    vg_quest_set_at_params(&_demo->quest.quest[MAIN_QUEST_2],
    0, 1, ITEM_APPLE, 0);
    vg_quest_set_loot(&_demo->quest.quest[MAIN_QUEST_2],
    ITEM_SWORD_2, 1, 10);

    _demo->quest.quest[MAIN_QUEST_3] = vg_quest_create(DIALOGUE_MAIN3_START
    , AT_KILL, &vg_next_mq);
    vg_quest_set_params_kill(&_demo->quest.quest[MAIN_QUEST_3], ENEMY_FISH, 1);
    vg_quest_set_loot(&_demo->quest.quest[MAIN_QUEST_3],
    ITEM_SWORD_3, 1, 20);

    _demo->quest.quest[MAIN_QUEST_BOSS] = vg_quest_create(DIALOGUE_MAINBOSS
    , AT_BOSS, &vg_end_storie);
    vg_quest_set_loot(&_demo->quest.quest[MAIN_QUEST_BOSS],
    ITEM_PLANE, 1, 100);
}

void quest_load(void)
{
    file_read_t file = file_read_create("maps/qst");

    _demo->quest.curr_main_quest = MAIN_QUEST_1;
    if (file.data == NULL)
        return;
    file_read(&file, &_demo->quest.curr_main_quest, sizeof(quests_list_t));
    file_read_flush(&file);
}

void quest_store(void)
{
    file_write_t file = file_write_create();

    file_write(&file, &_demo->quest.curr_main_quest, sizeof(quests_list_t));
    file_write_flush(&file, "maps/qst");
    _demo->quest.curr_main_quest = MAIN_QUEST_1;
    _demo->quest.fish_killed = 0;
}

void quest_init(void)
{
    quest_load();
    set_quest_dialogues();
    set_quest();
}