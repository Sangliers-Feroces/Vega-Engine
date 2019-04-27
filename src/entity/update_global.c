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

int entity3_global_update_actual(entity3 *ent)
{
    ssize2 chunk_pos = chunk_get_pos(dmat4_trans(ent->trans.world));

    if (is_root_child(ent)) {
        if ((!chunk_is_loaded(chunk_pos)) && (ent->tag != ENTITY3_TAG_PLAYER)) {
            world_chunk_send_global_ent(chunk_pos, ent);
            return 1;
        }
        if (!is_chunk_active(chunk_pos))
            return 0;
    }
    entity3_update_solo(ent);
    for (size_t i = 0; i < ent->sub.count; i++)
        if (entity3_global_update_actual(ent->sub.ent[i]))
            i--;
    return 0;
}

void entity3_global_update(entity3 *ent)
{
    entity3_update_solo(ent);
    for (size_t i = 0; i < ent->sub.count; i++)
        if (entity3_global_update_actual(ent->sub.ent[i]))
            i--;
}
