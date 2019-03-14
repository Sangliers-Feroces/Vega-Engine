/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** rect
*/

#include "headers.h"

int is_vec2_inside_rect(vec2 mouse_pos, rect_t button_rect)
{
    //printf("mp x : %f  mp y : %f\n rect x : %f  rect y : %f  rect x + size : %f  rect y + size %f\n", mouse_pos.x, mouse_pos.y, button_rect.p.x, -1 * button_rect.p.y, button_rect.p.x + button_rect.s.x, -1 * (button_rect.p.y + button_rect.s.y));
    if ((mouse_pos.x > button_rect.p.x &&
    mouse_pos.x < button_rect.p.x + button_rect.s.x)
    && (mouse_pos.y < -1 * button_rect.p.y &&
    mouse_pos.y > -1 * (button_rect.p.y + button_rect.s.y)))
        return 1;
    return 0;
}