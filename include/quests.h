/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** quests
*/

#pragma once

vg_quest vg_quest_create(dialogues_list_t start, archetype_t at, 
void (*ptr)(void));

void vg_quest_set_loot(vg_quest *src,
items_t loot, int nb_loot, float xp);
void vg_quest_set_at_params(vg_quest *src, float time_to_kill,
int nb_item_to_loot, items_t item_to_loot, int lvl);

void quest_init(void);
void quest_quit(void);
void set_quest_dialogues(void);
int quest_check_success(quests_list_t index);
void main_quest_start(void);
