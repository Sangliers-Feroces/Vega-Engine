/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

void entity3_trans_update_model(entity3 *ent)
{
    dmat4_model(&ent->trans, ent->trans.model, ent->trans.model_rot);
}

static void update_col(entity3 *ent)
{
    dvec3 p = dmat4_mul_dvec3(ent->trans.world, dvec3_init(0.0, 0.0, 0.0));
    double dist = dvec3_dist(dvec3_init(p.x, 0.0, p.z),
    dvec3_init(_demo->cam.pos.x, 0.0, _demo->cam.pos.z));

    entity3_set_col(ent, dist < (CHUNK_SIZE * 2.0));
}

void entity3_update_solo(entity3 *ent, dmat4 par_world, dmat4 par_rot)
{
    if (!ent->trans.is_static) {
        if (ent->trans.is_physics)
            entity3_physics(ent);
        entity3_trans_update_model(ent);
    }
    update_col(ent);
    if (par_world != NULL)
        dmat4_mul(par_world, ent->trans.model, ent->trans.world);
    else
        dmat4_copy(ent->trans.model, ent->trans.world);
    if (par_rot != NULL)
        dmat4_mul(par_rot, ent->trans.model_rot, ent->trans.world_rot);
    else
        dmat4_copy(ent->trans.model_rot, ent->trans.world_rot);
}

static void entity3_update_actual(entity3 *ent, dmat4 par_world, dmat4 par_rot)
{
    entity3_update_solo(ent, par_world, par_rot);
    for (size_t i = 0; i < ent->sub.count; i++)
        entity3_update_actual(ent->sub.ent[i],
        ent->trans.world, ent->trans.world_rot);
}

void entity3_update(entity3 *ent)
{
    entity3_update_actual(ent, NULL, NULL);
}
