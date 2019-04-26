/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

void entity3_set_child(entity3 *parent, entity3 *to_add)
{
    to_add->root_ndx = vec_entity3_add(&parent->sub, to_add);
    entity3_update_solo(to_add, parent->trans.world, parent->trans.world_rot);
}

void entity3_remove_from_parent(entity3 *ent)
{
    if (ent->root != NULL) {
        ent->root->sub.ent[ent->root_ndx] =
        ent->root->sub.ent[-- ent->root->sub.count];
        ent->root->sub.ent[ent->root_ndx]->root_ndx = ent->root_ndx;
        ent->root = NULL;
        ent->root_ndx = ~0ULL;
    }
}

entity3* chunk_add_entity(chunk_t *chunk)
{
    entity3 *res = entity3_create(chunk->ents);

    return res;
}
