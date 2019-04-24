/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

void check_mouse_move(demo_t *demo)
{
    float sensi = 0.0015f;

    if (_iu.data.is_invent)
        return;
    demo->world.player->trans.rot.y -=
    (float)(demo->mouse.mouse_pos.x - demo->mouse.last_pos.x) * sensi;
    demo->world.camera->trans.rot.x -=
    (float)(demo->mouse.mouse_pos.y - demo->mouse.last_pos.y) * sensi;
    demo->world.camera->trans.rot.x =
    CLAMP(demo->world.camera->trans.rot.x, -M_PI / 2.0, M_PI / 2.0);
}

static void poll_editor(demo_t *demo, dvec3 cam_x, dvec3 cam_z)
{
    dvec3 *p = &demo->world.player->trans.pos;

    if (sfKeyboard_isKeyPressed(sfKeyZ))
       *p = dvec3_add(*p, dvec3_muls(cam_z, CAM_MOVE));
    if (sfKeyboard_isKeyPressed(sfKeyS))
        *p = dvec3_sub(*p, dvec3_muls(cam_z, CAM_MOVE));
    if (sfKeyboard_isKeyPressed(sfKeyD))
        *p = dvec3_add(*p, dvec3_muls(cam_x, CAM_MOVE));
    if (sfKeyboard_isKeyPressed(sfKeyQ))
        *p = dvec3_sub(*p, dvec3_muls(cam_x, CAM_MOVE));
}

static void poll_playing(demo_t *demo, dvec3 cam_x, dvec3 cam_z)
{
    dvec3 *s = &demo->world.player->trans.speed;

    cam_z.y = 0.0;
    if (sfKeyboard_isKeyPressed(sfKeyZ))
        *s = dvec3_add(*s, dvec3_muls(cam_z, PLAYER_MOVE));
    if (sfKeyboard_isKeyPressed(sfKeyS))
        *s = dvec3_sub(*s, dvec3_muls(cam_z, PLAYER_MOVE));
    if (sfKeyboard_isKeyPressed(sfKeyD))
        *s = dvec3_add(*s, dvec3_muls(cam_x, PLAYER_MOVE));
    if (sfKeyboard_isKeyPressed(sfKeyQ))
        *s = dvec3_sub(*s, dvec3_muls(cam_x, PLAYER_MOVE));
    if (sfKeyboard_isKeyPressed(sfKeySpace) &&
    _demo->world.player->trans.is_grounded)
        s->y = 3.0;
    player_physics(demo);
}

static void poll_general(demo_t *demo)
{
    for (size_t i = 0; i < 256; i++)
        demo->input.key_last[i] = demo->input.key_state[i];
    for (size_t i = 0; i < 26; i++)
        demo->input.key_state['A' + i] = sfKeyboard_isKeyPressed(sfKeyA + i);
    demo->input.key_state[KEY_DEL] = sfKeyboard_isKeyPressed(sfKeyDelete);
    demo->input.key_state[KEY_ENTER] = sfKeyboard_isKeyPressed(sfKeyEnter);
    demo->input.key_state[KEY_TAB] = sfKeyboard_isKeyPressed(sfKeyTab);
    for (size_t i = 0; i < 256; i++)
        demo->input.key_press[i] =
        (!demo->input.key_last[i]) && demo->input.key_state[i];
}

void demo_poll_input(demo_t *demo)
{
    dvec3 cam_x = spherical_to_cartesian_z_to_x(demo->cam.rot);
    dvec3 cam_z = spherical_to_cartesian_z(demo->cam.rot);

    demo_update_framerate(demo);
    cam_x = dvec3_muls(cam_x, demo->win.framelen);
    cam_z = dvec3_muls(cam_z, demo->win.framelen);
    if (demo->world.player->trans.is_physics)
        poll_playing(demo, cam_x, cam_z);
    else
        poll_editor(demo, cam_x, cam_z);
    poll_general(demo);
}
