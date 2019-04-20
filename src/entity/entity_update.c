/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

void entity3_trans_update_model(entity3 *ent)
{
    dmat4_model(ent->trans.pos, ent->trans.scale, ent->trans.rot,
    ent->trans.model);
}

static void entity3_update_actual(entity3 *ent, dmat4 par_world)
{
    if (!ent->trans.is_static)
        entity3_trans_update_model(ent);
    if (par_world != NULL)
        dmat4_mul(par_world, ent->trans.model, ent->trans.world);
    else
        dmat4_copy(ent->trans.model, ent->trans.world);
    for (size_t i = 0; i < ent->sub.count; i++)
        entity3_update_actual(ent->sub.ent[i], ent->trans.world);
}

void entity3_update(entity3 *ent)
{
    entity3_update_actual(ent, NULL);
}
