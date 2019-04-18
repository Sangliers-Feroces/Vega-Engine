/*
** EPITECH PROJECT, 2019
** undefined
** File description:
** slider
*/

#include "headers.h"

static void move_slider(demo_t *demo, entity2_t *slider)
{
    vec2 screen = {demo->win.w , demo->win.h};
    vec2 mouse_posf = {demo->mouse.mouse_pos.x, demo->mouse.mouse_pos.y};
    vec2 relative_mouse_pos;

    relative_mouse_pos = vec2_muls(
    vec2_subs(vec2_div(mouse_posf, screen), 0.5f), 2.0f);
    relative_mouse_pos.y *= -1.0;
    slider->rect.p.x += (relative_mouse_pos.x - slider->rect.p.x);
}

static int check_slider_side(entity2_t slider)
{
    if (slider.slider->rect.p.x <= slider.x_min ||
        slider.slider->rect.p.x + slider.slider->rect.s.x >= slider.x_max) {
        return 1;
    }
    return 0;
}

float menu_slider_move(demo_t *demo, entity2_t *slider)
{
    float save_x;
    float segment_len;
    float segment_len2;

    save_x = slider->slider->rect.p.x;
    move_slider(demo, slider->slider);
    if (check_slider_side((*slider)))
        slider->slider->rect.p.x = save_x;
    segment_len = (slider->x_max - slider->x_min);
    segment_len2 = (slider->slider->rect.p.x - slider->x_min);
    segment_len *= 100;
    segment_len2 *= 100;
    return (segment_len2 / segment_len) - 0.05;
}
