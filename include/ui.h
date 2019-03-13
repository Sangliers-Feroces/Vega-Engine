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

void ui_draw_full_rel(texture2 *texture, vec2 pos, vec2 size);
void ui_draw_x(texture2 *texture, vec2 pos, float size);
void ui_draw_y(texture2 *texture, vec2 pos, float size);
void ui_display(int task, demo_t *demo);

#endif /* !UI_H_ */
