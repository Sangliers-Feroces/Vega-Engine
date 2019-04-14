/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static int try_unload_chunk(chunk_t *chunk, ssize2 cam)
{
    ssize_t dist = ssize2_dist_sq_man(chunk->pos, cam);

    if (chunk == NULL)
        return 0;
    if (dist > CHUNK_LOAD_DISTANCE) {
        chunk_destroy(chunk);
        return 1;
    } else
        return 0;
}

static void try_load_chunk(demo_t *demo, ssize2 pos)
{
    chunk_t **chunk = world_chunk2d_get(demo, pos);

    if (chunk == NULL)
        world_chunk_get(demo, pos);
    else if (*chunk == NULL)
        world_chunk_get(demo, pos);
}

void world_chunk_god(demo_t *demo)
{
    ssize2 cam = {demo->cam.pos.x / CHUNK_SIZE, demo->cam.pos.z / CHUNK_SIZE};

    for (size_t i = 0; i < demo->world.chunk_count; i++)
        if (try_unload_chunk(demo->world.chunk[i], cam))
            i--;
    for (ssize_t i = -CHUNK_LOAD_DISTANCE; i <= CHUNK_LOAD_DISTANCE; i++)
        for (ssize_t j = -CHUNK_LOAD_DISTANCE; j <= CHUNK_LOAD_DISTANCE; j++)
            try_load_chunk(demo, ssize2_add(cam, (ssize2){j, i}));
}
