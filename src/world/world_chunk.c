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
    chunk->terrain = chunk_entity_add(chunk);
    chunk_gen_terrain(chunk);
    entity_set_col(chunk->terrain, chunk->mesh_lod[WORLD_LOD_MAX]->mesh);
    for (size_t i = 0; i < 3; i++) {
        chunk->terrain->render[i].mesh = chunk->mesh_lod[i];
        chunk->terrain->render[i].material = MATERIAL_GRASS;
    }
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
    res->lod_count = WORLD_LOD_COUNT;
    for (size_t i = 0; i < res->lod_count; i++)
        res->lod[i] = chunk_lod_create(i);
    res->world_ndx = ~0ULL;
    res->ents = entity3_create(NULL);
    for (size_t i = 0; i < WORLD_LOD_COUNT + 1; i++)
        res->mesh_lod[i] = mesh_full_create(0, 1, 0);
    chunk_set_terrain(res);
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
    chunk_border_destroy(chunk->border);
    for (size_t i = 0; i < chunk->lod_count; i++)
        chunk_lod_destroy(&chunk->lod[i]);
    entity3_destroy(chunk->ents);
    for (size_t i = 0; i < WORLD_LOD_COUNT + 1; i++)
        mesh_full_destroy(chunk->mesh_lod[i]);
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

chunk_t* world_chunk_get_by_pos(demo_t *demo, dvec3 pos)
{
    return world_chunk_get(demo,
    (ssize2){pos.x / CHUNK_SIZE, pos.z / CHUNK_SIZE});
}

void chunk_insert_rtx_triangle(chunk_t *chunk, rtx_triangle *triangle)
{
    chunk_lod_insert_rtx_triangle(&chunk->lod[0], triangle);
}

void chunk_insert_rtx_triangle_lod(chunk_t *chunk, size_t lod,
rtx_triangle *triangle)
{
    chunk_lod_insert_rtx_triangle(&chunk->lod[lod], triangle);
}

