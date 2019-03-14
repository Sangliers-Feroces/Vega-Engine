/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** ui
*/

#ifndef UI_H_
#define UI_H_

#include "headers.h"

void ui_init(demo_t *demo);
void ui_quit(void);

void ui_draw_full_rel(uires_t index, vec2 pos, vec2 size);
void ui_draw_x(uires_t index, vec2 pos, float size);
void ui_draw_y(uires_t index, vec2 pos, float size);
void ui_display(int task, demo_t *demo);

void ui_set_textures_to_null(void);
void ui_load_texture(const ui_texture_descriptor_t descriptors_array[]);
void ui_set_buttons(void);

#endif /* !UI_H_ */
