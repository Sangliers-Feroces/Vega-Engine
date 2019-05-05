/*
** EPITECH PROJECT, 2019
** MUL_my_world_2018
** File description:
** menu
*/

#pragma once

int start(demo_t *demo);

void menu_init(menu_t *menu);

void menu_set_entities(menu_t *menu);

int menu_loop(demo_t *demo, menu_t *menu);

void menu_draw(menu_t *menu);
int intro(void);
void menu_display_help(menu_t *menu);

int menu_poll_events(demo_t *demo, menu_t *menu);
float menu_slider_move(demo_t *demo, entity2_t *slider);
