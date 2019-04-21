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
        return
        &demo->world.chunk2d[ndx.y * demo->world.chunk2d_area.s.x + ndx.x];
}

static void chunk_set_terrain(chunk_t *chunk)
{
    chunk->terrain = chunk_add_entity(chunk);
    chunk_gen_terrain(chunk, chunk->terrain);
    entity3_update(chunk->ents);
    entity3_set_col(chunk->terrain,
    entity3_get_lod_ref(chunk->terrain, WORLD_LOD_MAX));
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
    res->world_ndx = ~0ULL;
    res->ents = entity3_create_pos(NULL,
    dvec3_init(pos.x * CHUNK_SIZE, 0.0, pos.y * CHUNK_SIZE));
    chunk_set_terrain(res);
    res->inserting = NULL;
    world_chunk2d_insert(_demo, res);
    world_chunk_add(_demo, res);
    return res;
}

void chunk_destroy(chunk_t *chunk)
{
    chunk_t **lookup;

    file_write_t write = file_write_create();
    file_write_entity3(&write, chunk->ents);
    entity3_destroy(file_read_entity3(&(file_read_t){0, write.size, write.data}, NULL));
    file_write_flush(&write, NULL);
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
    chunk_border_destroy(chunk->border);
    entity3_destroy(chunk->ents);
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

ssize2 chunk_get_pos(dvec3 pos)
{
    ssize2 res;

    res.x = pos.x / CHUNK_SIZE - (pos.x < 0.0 ? 1 : 0);
    res.y = pos.z / CHUNK_SIZE - (pos.z < 0.0 ? 1 : 0);
    return res;
}

chunk_t* world_chunk_get_by_pos(dvec3 pos)
{
    return world_chunk_get(_demo, chunk_get_pos(pos));
}

void chunk_update(chunk_t *chunk)
{
    entity3_update(chunk->ents);
}
