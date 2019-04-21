/*
** EPITECH PROJECT, 2019
** MUL_my_world_2018
** File description:
** iu
*/

#pragma once

void iu_init(demo_t *demo);
void set_entities(void);

rect_t entity_get_size(entity2_t entity);
void iu_display(void);

void iu_entity_draw(entity2_t entity);

void entity_constructor(entity2_t *entity, entity2_param_t params);

void iu_text_init(void);
void iu_quit(void);

int check_click_pos(sfVector2i mouse_pos, entity2_t button,
float width_screen, float height);

void iu_display_grp(text_grp_ind_t index);

void iu_set_font(void);

void display_str_temp(char *str, rect_t start, font_list_t font);

void iu_display_char(char c, rect_t pos, font_list_t index);