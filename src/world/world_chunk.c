/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

void world_chunk_add(chunk_t *chunk)
{
    size_t cur = _demo->world.chunk_count++;
    chunk_t **new_chunk;

    if (_demo->world.chunk_count > _demo->world.chunk_allocated) {
        _demo->world.chunk_allocated += 16;
        new_chunk =
        (chunk_t**)malloc_safe(_demo->world.chunk_allocated * sizeof(chunk_t*));
        for (size_t i = 0; i < cur; i++)
            new_chunk[i] = _demo->world.chunk[i];
        free(_demo->world.chunk);
        _demo->world.chunk = new_chunk;
    }
    _demo->world.chunk[cur] = chunk;
    chunk->world_ndx = cur;
}

chunk_t** world_chunk2d_get(ssize2 pos)
{
    ssize2 ndx = ssize2_sub(pos, _demo->world.chunk2d_area.p);

    if (!((ndx.x >= 0) && (ndx.x < _demo->world.chunk2d_area.s.x) &&
    (ndx.y >= 0) && (ndx.y < _demo->world.chunk2d_area.s.y)))
        return NULL;
    else
        return
        &_demo->world.chunk2d[ndx.y * _demo->world.chunk2d_area.s.x + ndx.x];
}

static void chunk_set_terrain(chunk_t *chunk)
{
    if (chunk->terrain != NULL)
        return;
    chunk_gen_terrain(chunk->pos);
}

chunk_t* chunk_create_detached(ssize2 pos)
{
    chunk_t *res;

    res = (chunk_t*)malloc_safe(sizeof(chunk_t));
    res->pos = pos;
    res->border = chunk_border_init();
    res->border_ter = chunk_border_init();
    res->terrain_base = (arr2d_dvec3_t){0, 0, NULL};
    res->world_ndx = ~0ULL;
    res->ents = entity3_create_pos(NULL,
    dvec3_init(pos.x * CHUNK_SIZE, 0.0, pos.y * CHUNK_SIZE));
    res->inserting = NULL;
    res->terrain = NULL;
    res->is_stalled = 1;
    return res;
}

void chunk_attach(chunk_t *chunk)
{
    world_chunk2d_insert(chunk);
    world_chunk_add(chunk);
}

chunk_t* chunk_create_adv(ssize2 pos, int do_gen)
{
    chunk_t *res;
    chunk_t **pexist;

    pexist = world_chunk2d_get(pos);
    if (pexist != NULL)
        if (*pexist != NULL)
            return *pexist;
    res = chunk_create_detached(pos);
    chunk_attach(res);
    if (do_gen)
        chunk_set_terrain(res);
    return res;
}

chunk_t* chunk_create(ssize2 pos)
{
    return chunk_create_adv(pos, 1);
}

void chunk_destroy(chunk_t *chunk)
{
    chunk_t **lookup;

    if (chunk == NULL)
        return;
    chunk_save(chunk);
    lookup = world_chunk2d_get(chunk->pos);
    if (lookup != NULL)
        *lookup = NULL;
    if (chunk->world_ndx != ~0ULL) {
        _demo->world.chunk[chunk->world_ndx] =
        _demo->world.chunk[--_demo->world.chunk_count];
        _demo->world.chunk[chunk->world_ndx]->world_ndx = chunk->world_ndx;
    }
    chunk_border_destroy(chunk->border);
    chunk_border_destroy(chunk->border_ter);
    arr2d_dvec3_destroy(chunk->terrain_base);
    entity3_destroy(chunk->ents);
    free(chunk);
}

chunk_t* world_chunk_get_adv(ssize2 pos, int do_load, int do_gen)
{
    chunk_t **pexist = world_chunk2d_get(pos);
    chunk_t *res;

    if (pexist != NULL)
        if (*pexist != NULL)
            return *pexist;
    if (do_load)
        if (chunk_try_load(pos, &res))
            return res;
    return chunk_create_adv(pos, do_gen);
}

chunk_t* world_chunk_get(ssize2 pos)
{
    return world_chunk_get_adv(pos, 1, 1);
}

ssize2 chunk_get_pos(dvec3 pos)
{
    ssize2 res;

    res.x = pos.x / CHUNK_SIZE - (pos.x < 0.0 ? 1 : 0);
    res.y = pos.z / CHUNK_SIZE - (pos.z < 0.0 ? 1 : 0);
    return res;
}

ssize2 chunk_get_terrain_pos(ssize2 chunk_pos)
{
    ssize2 res;

    if (chunk_pos.x >= 0)
        res.x = chunk_pos.x / CHUNK_TERRAIN_SUB_SIZE;
    else
        res.x = (chunk_pos.x + 1) / CHUNK_TERRAIN_SUB_SIZE - 1;
    if (chunk_pos.y >= 0)
        res.y = chunk_pos.y / CHUNK_TERRAIN_SUB_SIZE;
    else
        res.y = (chunk_pos.y + 1) / CHUNK_TERRAIN_SUB_SIZE - 1;
    return res;
}

chunk_t* world_chunk_get_by_pos(dvec3 pos)
{
    return world_chunk_get(chunk_get_pos(pos));
}
