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

void ui_draw_full_rel(uires_t index, rect_t rect);
void button_draw(button_t button);
void ui_display(int task, demo_t *demo);

void ui_set_textures_to_null(void);
void ui_load_texture(const ui_texture_descriptor_t descriptors_array[]);
void ui_set_buttons(void);

void ui_swicth_button_action(void);
void ui_check_click_button(demo_t *demo);
rect_t button_get_size(button_t button);

void demo_set_cam_to_origin(demo_t *demo);
void ui_button_effect(demo_t *demo);

#endif /* !UI_H_ */
