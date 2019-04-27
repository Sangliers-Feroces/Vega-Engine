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

void entity3_update_solo(entity3 *ent, dmat4 par_world, dmat4 par_rot)
{
    if (_demo->world.tag_update[ent->tag] != NULL)
        _demo->world.tag_update[ent->tag](ent);
    if (!ent->trans.is_static) {
        if (ent->trans.is_physics)
            entity3_physics(ent);
        entity3_trans_update_model(ent);
    }
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
