/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static void chunk_update(chunk_t *chunk)
{
    if (chunk->is_stalled)
        return;
    entity3_update(chunk->ents);
    while (chunk->ents_global->sub.count > 0)
        entity3_move(chunk->ents_global->sub.ent[0], _demo->world.ents);
}

void world_update(void)
{
    world_chunk_god();
    for (size_t i = 0; i < _demo->world.chunk_count; i++)
        chunk_update(_demo->world.chunk[i]);
    entity3_global_update(_demo->world.ents);
    world_update_triggers();
    refresh_vp(_demo);
}
