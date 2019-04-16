/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** ui_buttons
*/

#include "headers.h"

int check_click_pos(sfVector2i mouse_pos, entity2_t button,
float width_screen, float height)
{
    vec2 screen = {width_screen, height};
    vec2 mouse_posf = {mouse_pos.x, mouse_pos.y};
    vec2 relative_mouse_pos;

    relative_mouse_pos = vec2_muls(
    vec2_subs(vec2_div(mouse_posf, screen), 0.5f), 2.0f);
    relative_mouse_pos.y *= -1.0;
    return rect_is_vec2_inside(button.rect, relative_mouse_pos);
}

void demo_set_cam_to_origin(demo_t *demo)
{
    demo->cam.pos = (dvec3){-5.0f, 8.0f, -5.0f};
    demo->cam.rot = (dvec3){-M_PI / 4.0f, -M_PI / 4.0f, 0.0f};
    if (demo->player.state == GAME_PLAYING)
        demo->player.pos = dvec3_sub(demo->cam.pos,
        (dvec3){0.0f, 1.75f, 0.0f});
}
