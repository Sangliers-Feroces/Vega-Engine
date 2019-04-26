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

void entity3_tag_update_player(entity3 *ent)
{
    dvec3 cam_x;
    dvec3 cam_z;
    entity3 *ref_move = ent->trans.is_physics ? ent : ent->sub.ent[0];

    entity3_tag_update_player_poll_mouse(ent);
    cam_x = dvec3_muls(dmat4_mul_dvec3(ref_move->trans.world_rot,
    dvec3_init(1.0, 0.0, 0.0)), _demo->win.framelen);
    cam_z = dvec3_muls(dmat4_mul_dvec3(ref_move->trans.world_rot,
    dvec3_init(0.0, 0.0, 1.0)), _demo->win.framelen);
    if (ent->trans.is_physics)
        entity3_tag_update_player_poll_playing(ent, cam_x, cam_z);
    else
        entity3_tag_update_player_poll_editor(ent, cam_x, cam_z);
    if (ent->trans.is_grounded)
        slow_ent_down(ent);
    cap_ent_speed(&ent->trans.speed);
}
