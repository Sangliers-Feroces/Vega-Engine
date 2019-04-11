/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

void world_chunk_add(demo_t *demo, chunk_t *chunk)
{
    size_t cur = demo->world.chunk_count++;
    chunk_t **new_chunk;

    if (demo->world.chunk_count > demo->world.chunk_allocated) {
        demo->world.chunk_allocated += 16;
        new_chunk =
        (chunk_t**)malloc_safe(demo->world.chunk_allocated * sizeof(chunk_t*));
        for (size_t i = 0; i < cur; i++)
            new_chunk[i] = demo->world.chunk[i];
        free(demo->world.chunk);
        demo->world.chunk = new_chunk;
    }
    demo->world.chunk[cur] = chunk;
    chunk->world_ndx = cur;
}

chunk_t** world_chunk2d_get(demo_t *demo, ssize2 pos)
{
    ssize2 ndx = ssize2_sub(pos, demo->world.chunk2d_area.p);

    if (!((ndx.x >= 0) && (ndx.x < demo->world.chunk2d_area.s.x) &&
    (ndx.y >= 0) && (ndx.y < demo->world.chunk2d_area.s.y)))
        return NULL;
    else
        return &demo->world.chunk2d[ndx.y * demo->world.chunk2d_area.s.x + ndx.x];
}

chunk_t* chunk_create(ssize2 pos)
{
    chunk_t *res;
    chunk_t **pexist;

    pexist = world_chunk2d_get(_demo, pos);
    if (pexist != NULL)
        if (*pexist != NULL)
            return *pexist;
    res = (chunk_t*)malloc_safe(sizeof(chunk_t));
    res->pos = pos;
    res->tree = octree_create(NULL);
    res->world_ndx = ~0ULL;
    world_chunk2d_insert(_demo, res);
    world_chunk_add(_demo, res);
    return res;
}

void chunk_destroy(chunk_t *chunk)
{
    chunk_t **lookup;

    if (chunk == NULL)
        return;
    lookup = world_chunk2d_get(_demo, chunk->pos);
    if (lookup != NULL)
        *lookup = NULL;
    if (chunk->world_ndx != ~0ULL) {
        _demo->world.chunk[chunk->world_ndx] =
        _demo->world.chunk[--_demo->world.chunk_count];
        _demo->world.chunk[chunk->world_ndx]->world_ndx = chunk->world_ndx;
    }
    octree_destroy(&chunk->tree);
    free(chunk);
}

chunk_t* world_chunk_get(demo_t *demo, ssize2 pos)
{
    chunk_t **pexist = world_chunk2d_get(demo, pos);

    if (pexist != NULL)
        if (*pexist != NULL)
            return *pexist;
    return chunk_create(pos);
}

chunk_t* world_chunk_get_by_pos(demo_t *demo, vec3 pos)
{
    return world_chunk_get(demo,
    (ssize2){pos.x / CHUNK_SIZE, pos.z / CHUNK_SIZE});
}

void chunk_insert_rtx_triangle(chunk_t *chunk, rtx_triangle *triangle)
{
    octree_insert_triangle(&chunk->tree, triangle);
}
