/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** ui_buttons
*/

#include "headers.h"

void demo_set_cam_to_origin(demo_t *demo)
{
    demo->cam.pos = (vec3){-5.0f, 8.0f, -5.0f};
    demo->cam.rot = (vec3){-M_PI / 4.0f, -M_PI / 4.0f, 0.0f};
    if (demo->player.state == GAME_PLAYING)
        demo->player.pos = vec3_sub(demo->cam.pos,
        (vec3){0.0f, 1.75f, 0.0f});
}
