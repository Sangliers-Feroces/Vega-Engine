/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

int world_is_chunk_active(ssize2 chunk_pos)
{
    chunk_t **pexist = world_chunk2d_get(chunk_pos);

    if ((pexist == NULL) || (*pexist == NULL))
        return 0;
    return !(*pexist)->is_stalled;
}

int try_unload_ent(entity3 *ent)
{
    ssize2 chunk_pos = chunk_get_pos(dmat4_trans(ent->trans.world));

    if ((!chunk_is_loaded(chunk_pos)) && (ent->tag != ENTITY3_TAG_PLAYER)) {
        world_chunk_send_global_ent(chunk_pos, ent);
        return 1;
    }
    return 0;
}

void entity3_global_update(entity3 *ent)
{
    entity3_update_solo(ent);
    for (size_t i = 0; i < ent->sub.count; i++) {
        if (world_is_pos_col_oob(dmat4_trans(ent->sub.ent[i]->trans.world))) {
            i -= try_unload_ent(ent->sub.ent[i]);
            continue;
        }
        entity3_update(ent->sub.ent[i]);
    }
}
