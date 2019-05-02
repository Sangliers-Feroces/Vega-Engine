/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

void entity3_tag_update_enemy(entity3 *ent)
{
    entity3_tag_enemy_data_t *data = ent->tag_data;
    dvec3 p = dmat4_trans(_demo->world.player->trans.world);
    dvec3 e = dmat4_trans(ent->trans.world);
    dvec3 v = dvec3_sub(p, e);
    double dist = dvec3_dist_sq(dmat4_trans(ent->trans.world), p);
    dvec3 d;
    double a_dif = atan2(v.z, v.x) - ent->trans.rot.y;

    if (dist < (32.0 * 32.0)) {
        ent->trans.rot.y += a_dif *
        _demo->win.framelen * 4.0 * ent->trans.is_grounded;
        d = dvec3_muls(dmat4_mul_dvec3(ent->trans.world_rot,
        dvec3_init(1.0, 0.0, 0.0)), _demo->win.framelen * 10.0);
        ent->trans.speed = dvec3_add(ent->trans.speed, d);
    }
    if ((dist < (4.0 * 4.0)) && ent->trans.is_grounded && (fabs(a_dif) < 0.5))
        ent->trans.speed.y = 5.0;
    player_update(ent, data->max_speed);
}

void entity3_tag_init_enemy(void *pdata)
{
    (void)pdata;
}
