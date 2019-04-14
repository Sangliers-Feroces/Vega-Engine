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

static ssize2 get_chunk_cam(vec3 pos)
{
    ssize2 res;

    res.x = pos.x / CHUNK_SIZE - (pos.x < 0.0 ? 1 : 0);
    res.y = pos.z / CHUNK_SIZE - (pos.z < 0.0 ? 1 : 0);
    return res;
}

void world_chunk_god(demo_t *demo)
{
    ssize2 cam = get_chunk_cam(demo->cam.pos);

    for (size_t i = 0; i < demo->world.chunk_count; i++)
        if (try_unload_chunk(demo->world.chunk[i], cam))
            i--;
    for (ssize_t i = -CHUNK_LOAD_DISTANCE; i <= CHUNK_LOAD_DISTANCE; i++)
        for (ssize_t j = -CHUNK_LOAD_DISTANCE; j <= CHUNK_LOAD_DISTANCE; j++)
            try_load_chunk(demo, ssize2_add(cam, (ssize2){j, i}));
}
