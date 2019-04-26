/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static void slow_ent_down(entity3 *ent)
{
    ent->trans.speed.x *= 1.0 - _demo->win.framelen * 6.0;
    ent->trans.speed.z *= 1.0 - _demo->win.framelen * 6.0;
}

static void cap_ent_speed(dvec3 *speed)
{
    vec2 xz = {speed->x, speed->z};
    float dist = vec2_norm(xz);

    if (dist > PLAYER_MAX_SPEED) {
        xz = vec2_muls(xz, PLAYER_MAX_SPEED / dist);
        *speed = (dvec3){xz.x, speed->y, xz.y};
    }
}

static void poll_mouse_move(entity3 *ent)
{
    float sensi = 0.0015f;

    if (_iu.data.is_invent)
        return;
    ent->trans.rot.y -=
    (float)(_demo->mouse.mouse_pos.x - _demo->mouse.last_pos.x) * sensi;
    ent->sub.ent[0]->trans.rot.x -=
    (float)(_demo->mouse.mouse_pos.y - _demo->mouse.last_pos.y) * sensi;
    ent->sub.ent[0]->trans.rot.x =
    CLAMP(ent->sub.ent[0]->trans.rot.x, -M_PI / 2.0, M_PI / 2.0);
}

static void poll_editor(entity3 *ent, dvec3 cam_x, dvec3 cam_z)
{
    dvec3 *p = &ent->trans.pos;

    if (sfKeyboard_isKeyPressed(sfKeyZ))
       *p = dvec3_add(*p, dvec3_muls(cam_z, CAM_MOVE));
    if (sfKeyboard_isKeyPressed(sfKeyS))
        *p = dvec3_sub(*p, dvec3_muls(cam_z, CAM_MOVE));
    if (sfKeyboard_isKeyPressed(sfKeyD))
        *p = dvec3_add(*p, dvec3_muls(cam_x, CAM_MOVE));
    if (sfKeyboard_isKeyPressed(sfKeyQ))
        *p = dvec3_sub(*p, dvec3_muls(cam_x, CAM_MOVE));
}

static void poll_playing(entity3 *ent, dvec3 cam_x, dvec3 cam_z)
{
    dvec3 *s = &ent->trans.speed;

    cam_z.y = 0.0;
    if (sfKeyboard_isKeyPressed(sfKeyZ))
        *s = dvec3_add(*s, dvec3_muls(cam_z, PLAYER_MOVE));
    if (sfKeyboard_isKeyPressed(sfKeyS))
        *s = dvec3_sub(*s, dvec3_muls(cam_z, PLAYER_MOVE));
    if (sfKeyboard_isKeyPressed(sfKeyD))
        *s = dvec3_add(*s, dvec3_muls(cam_x, PLAYER_MOVE));
    if (sfKeyboard_isKeyPressed(sfKeyQ))
        *s = dvec3_sub(*s, dvec3_muls(cam_x, PLAYER_MOVE));
    if (sfKeyboard_isKeyPressed(sfKeySpace) && ent->trans.is_grounded)
        s->y = 3.0;
}

void entity3_tag_update_player(entity3 *ent)
{
    dvec3 cam_x;
    dvec3 cam_z;

    poll_mouse_move(ent);
    cam_x = dvec3_muls(dmat4_mul_dvec3(ent->sub.ent[0]->trans.world_rot,
    dvec3_init(1.0, 0.0, 0.0)), _demo->win.framelen);
    cam_z = dvec3_muls(dmat4_mul_dvec3(ent->sub.ent[0]->trans.world_rot,
    dvec3_init(0.0, 0.0, 1.0)), _demo->win.framelen);
    if (ent->trans.is_physics)
        poll_playing(ent, cam_x, cam_z);
    else
        poll_editor(ent, cam_x, cam_z);
    if (ent->trans.is_grounded)
        slow_ent_down(ent);
    cap_ent_speed(&ent->trans.speed);
}
