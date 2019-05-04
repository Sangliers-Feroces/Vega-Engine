/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** quests_struct
*/

#pragma once

typedef enum {
    MAIN_QUEST_1,
    MAIN_QUEST_2,
    MAIN_QUEST_BOSS,
    /*SIDE_QUEST_LOOT_1,
    SIDE_QUEST_TIME_1,*/
    QUEST_END,
    NO_QUEST
} quests_list_t;

typedef enum {
    AT_TIME,
    AT_LOOT,
    AT_LVL
} archetype_t;

typedef struct {
    int did;
    dialogues_list_t first_dial;
    archetype_t at;
    //params_at
    items_t item_to_loot;
    int nb;
    float time_to_kill;
    int lvl;
    int start_choice;
    void (*next_step)(void);
    //loot
    items_t loot;
    int nb_loot;
    float xp_looted;
} vg_quest;

typedef struct {
    quests_list_t curr_main_quest;
    vg_quest quest[QUEST_END];
} quests_t;