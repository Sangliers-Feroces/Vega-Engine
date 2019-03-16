/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

void demo_init_input(demo_t *demo)
{
    demo->input.binding[KEY_UP] = sfKeyUp;
    demo->input.binding[KEY_DOWN] = sfKeyDown;
    demo->input.binding[KEY_LEFT] = sfKeyLeft;
    demo->input.binding[KEY_RIGHT] = sfKeyRight;
    demo->input.binding[KEY_JUMP] = sfKeyX;
    demo->input.binding[KEY_ATK] = sfKeyW;
    demo->input.binding[KEY_UI] = sfKeyP;
}

static void poll_editor(demo_t *demo, vec3 cam_x, vec3 cam_z)
{
    if (sfKeyboard_isKeyPressed(sfKeyZ))
        demo->cam.pos =
        vec3_add(demo->cam.pos, vec3_muls(cam_z, CAM_MOVE));
    if (sfKeyboard_isKeyPressed(sfKeyS))
        demo->cam.pos =
        vec3_sub(demo->cam.pos, vec3_muls(cam_z, CAM_MOVE));
    if (sfKeyboard_isKeyPressed(sfKeyD))
        demo->cam.pos =
        vec3_add(demo->cam.pos, vec3_muls(cam_x, CAM_MOVE));
    if (sfKeyboard_isKeyPressed(sfKeyQ))
        demo->cam.pos =
        vec3_sub(demo->cam.pos, vec3_muls(cam_x, CAM_MOVE));
}

static void poll_playing(demo_t *demo, vec3 cam_x, vec3 cam_z)
{
    cam_z.y = 0.0;
    if (sfKeyboard_isKeyPressed(sfKeyZ))
        demo->player.speed =
        vec3_add(demo->player.speed, vec3_muls(cam_z, PLAYER_MOVE));
    if (sfKeyboard_isKeyPressed(sfKeyS))
        demo->player.speed =
        vec3_sub(demo->player.speed, vec3_muls(cam_z, PLAYER_MOVE));
    if (sfKeyboard_isKeyPressed(sfKeyD))
        demo->player.speed =
        vec3_add(demo->player.speed, vec3_muls(cam_x, PLAYER_MOVE));
    if (sfKeyboard_isKeyPressed(sfKeyQ))
        demo->player.speed =
        vec3_sub(demo->player.speed, vec3_muls(cam_x, PLAYER_MOVE));
    if (sfKeyboard_isKeyPressed(sfKeySpace) && demo->player.is_grounded)
        demo->player.speed.y = 3.0f;
    if (sfKe)
    player_physics(demo);
}

void demo_poll_input(demo_t *demo)
{
    vec3 cam_x = spherical_to_cartesian_z_to_x(demo->cam.rot);
    vec3 cam_z = spherical_to_cartesian_z(demo->cam.rot);

    demo_update_framerate(demo);
    cam_x = vec3_muls(cam_x, demo->win.framelen);
    cam_z = vec3_muls(cam_z, demo->win.framelen);
    for (size_t i = 0; i < KEY_COUNT; i++)
        demo->input.keystate[i] =
        sfKeyboard_isKeyPressed(demo->input.binding[i]);
    if (demo->player.state == GAME_EDITOR)
        poll_editor(demo, cam_x, cam_z);
    else
        poll_playing(demo, cam_x, cam_z);
}
