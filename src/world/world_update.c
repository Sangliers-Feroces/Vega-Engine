/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static void chunk_update(chunk_t *chunk)
{
    if (!chunk->is_stalled)
        entity3_update(chunk->ents);
}

void world_update(void)
{
    for (size_t i = 0; i < _demo->world.chunk_count; i++)
        chunk_update(_demo->world.chunk[i]);
    entity3_update(_demo->world.ents);
    refresh_vp(_demo);
    world_chunk_god();
}
