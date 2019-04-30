/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** invent
*/

#pragma once

void invent_init(void);

int invent_poll_event(void);

void invent_loop(void);

char *invent_get_item_type(void);
char *invent_get_item_value(void);
int invent_get_item_data(void);
void invent_display_icon(void);

void invent_draw_button(void);