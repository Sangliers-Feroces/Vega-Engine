/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static int get_stalled(chunk_t *chunk)
{
    for (ssize_t i = -1; i <= 1; i++)
        for (ssize_t j = -1; j <= 1; j++)
            if (!chunk_is_loaded(ssize2_add(chunk->pos, (ssize2){j, i})))
                return 1;
    return 0;
}

void world_chunk_god_stalled(void)
{
    for (size_t i = 0; i < _demo->world.chunk_count; i++)
        _demo->world.chunk[i]->is_stalled =
        get_stalled(_demo->world.chunk[i]);
}
