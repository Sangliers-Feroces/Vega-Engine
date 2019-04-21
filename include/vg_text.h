/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** vg_text
*/

#pragma once

vg_text vg_text_create(char *str, char *optional_value);

void vg_text_set_position(vg_text *src, vec2 pos);
void vg_text_set_size(vg_text *src, vec2 size);
void vg_text_reset_str(vg_text *src, char *str, char *optional_value);
void vg_text_set_font(vg_text *src, font_list_t font_index);

void vg_text_draw(vg_text src);