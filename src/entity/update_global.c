/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static int is_root_child(entity3 *ent)
{
    if (ent->root == NULL)
        return 0;
    return ent->root->root == NULL;
}

static int is_chunk_active(ssize2 chunk_pos)
{
    chunk_t **pexist = world_chunk2d_get(chunk_pos);

    if ((pexist == NULL) || (*pexist == NULL))
        return 0;
    return !(*pexist)->is_stalled;
}

static void entity3_global_update_actual(entity3 *ent, dmat4 par_world,
dmat4 par_rot)
{
    ssize2 chunk_pos = chunk_get_pos(dmat4_trans(ent->trans.world));

    if (is_root_child(ent)) {
        if ((!chunk_is_loaded(chunk_pos)) && (ent->tag != ENTITY3_TAG_PLAYER)) {
            world_chunk_send_global_ent(chunk_pos, ent);
            return;
        }
        if (!is_chunk_active(chunk_pos))
            return;
    }
    entity3_update_solo(ent, par_world, par_rot);
    for (size_t i = 0; i < ent->sub.count; i++)
        entity3_global_update_actual(ent->sub.ent[i],
        ent->trans.world, ent->trans.world_rot);
}

void entity3_global_update(entity3 *ent)
{
    entity3_global_update_actual(ent, NULL, NULL);
}
