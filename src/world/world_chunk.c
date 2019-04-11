/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

chunk_t** world_chunk2d_get(demo_t *demo, ssize2 pos)
{
    ssize2 ndx = ssize2_sub(pos, demo->world.chunk2d_area.p);

    if (!((ndx.x >= 0) && (ndx.x < demo->world.chunk2d_area.s.x) &&
    (ndx.y >= 0) && (ndx.y < demo->world.chunk2d_area.s.y)))
        return NULL;
    else
        return &demo->world.chunk2d[ndx.y * demo->world.chunk2d_area.s.x + ndx.x];
}

static void world_chunk2d_realloc_x_neg(demo_t *demo, size_t offset)
{
    size_t new_w = demo->world.chunk2d_area.s.x + offset;
    chunk_t** new_chunk2d = (chunk_t**)malloc_safe(
    new_w * demo->world.chunk2d_area.p.y * sizeof(chunk_t**));

    for (ssize_t i = 0; i < demo->world.chunk2d_area.s.y; i++) {
        for (size_t j = 0; j < offset; j++)
            new_chunk2d[i * new_w + j] = NULL;
        for (ssize_t j = 0; j < demo->world.chunk2d_area.s.x ; j++)
            new_chunk2d[i * new_w + offset + j] =
            demo->world.chunk2d[i * demo->world.chunk2d_area.s.x + j];
    }
    demo->world.chunk2d_area.p.x -= offset;
    demo->world.chunk2d_area.s.x = new_w;
    free(demo->world.chunk2d);
    demo->world.chunk2d = new_chunk2d;
}

static void world_chunk2d_realloc_x_pos(demo_t *demo, size_t offset)
{
    size_t new_w = demo->world.chunk2d_area.s.x + offset;
    chunk_t** new_chunk2d = (chunk_t**)malloc_safe(
    new_w * demo->world.chunk2d_area.p.y * sizeof(chunk_t**));

    for (ssize_t i = 0; i < demo->world.chunk2d_area.s.y; i++) {
        for (size_t j = 0; j < offset; j++)
            new_chunk2d[i * new_w + demo->world.chunk2d_area.s.x + j] = NULL;
        for (ssize_t j = 0; j < demo->world.chunk2d_area.s.x ; j++)
            new_chunk2d[i * new_w + j] =
            demo->world.chunk2d[i * demo->world.chunk2d_area.s.x + j];
    }
    demo->world.chunk2d_area.p.x -= offset;
    demo->world.chunk2d_area.s.x = new_w;
    free(demo->world.chunk2d);
    demo->world.chunk2d = new_chunk2d;
}

static void world_chunk2d_realloc_y_neg(demo_t *demo, size_t offset)
{
    size_t new_w = demo->world.chunk2d_area.s.x;
    size_t new_h = demo->world.chunk2d_area.s.y + offset;
    chunk_t** new_chunk2d = (chunk_t**)malloc_safe(
    new_w * new_h * sizeof(chunk_t**));

    for (size_t i = 0; i < offset; i++)
        for (ssize_t j = 0; j < demo->world.chunk2d_area.s.x; j++)
            new_chunk2d[i * new_w + j] = NULL;
    for (ssize_t i = 0; i < demo->world.chunk2d_area.s.y; i++)
        for (ssize_t j = 0; j < demo->world.chunk2d_area.s.x; j++)
            new_chunk2d[(offset + i) * new_w + j] =
            demo->world.chunk2d[i * demo->world.chunk2d_area.s.x + j];
    demo->world.chunk2d_area.p.y -= offset;
    demo->world.chunk2d_area.s.y = new_h;
    free(demo->world.chunk2d);
    demo->world.chunk2d = new_chunk2d;
}

static void world_chunk2d_realloc_y_pos(demo_t *demo, size_t offset)
{
    size_t new_w = demo->world.chunk2d_area.s.x;
    size_t new_h = demo->world.chunk2d_area.s.y + offset;
    chunk_t** new_chunk2d = (chunk_t**)malloc_safe(
    new_w * new_h * sizeof(chunk_t**));

    for (size_t i = 0; i < offset; i++)
        for (ssize_t j = 0; j < demo->world.chunk2d_area.s.x; j++)
            new_chunk2d[i * new_w + demo->world.chunk2d_area.s.x + j] = NULL;
    for (ssize_t i = 0; i < demo->world.chunk2d_area.s.y; i++)
        for (ssize_t j = 0; j < demo->world.chunk2d_area.s.x; j++)
            new_chunk2d[i * new_w + j] =
            demo->world.chunk2d[i * demo->world.chunk2d_area.s.x + j];
    demo->world.chunk2d_area.p.y -= offset;
    demo->world.chunk2d_area.s.y = new_h;
    free(demo->world.chunk2d);
    demo->world.chunk2d = new_chunk2d;
}

void world_chunk2d_insert(demo_t *demo, chunk_t *chunk)
{
    ssize_t border;

    border = demo->world.chunk2d_area.p.x;
    if (chunk->pos.x < border)
        world_chunk2d_realloc_x_neg(demo, border - chunk->pos.x);
    border = demo->world.chunk2d_area.p.x + demo->world.chunk2d_area.s.x;
    if (chunk->pos.x >= border)
        world_chunk2d_realloc_x_pos(demo, chunk->pos.x - (border - 1));
    border = demo->world.chunk2d_area.p.y;
    if (chunk->pos.y < border)
        world_chunk2d_realloc_y_neg(demo, border - chunk->pos.y);
    border = demo->world.chunk2d_area.p.y + demo->world.chunk2d_area.s.y;
    if (chunk->pos.y >= border)
        world_chunk2d_realloc_y_pos(demo, chunk->pos.y - (border - 1));
    *world_chunk2d_get(demo, chunk->pos) = chunk;
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
    world_chunk2d_insert(_demo, res);
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
