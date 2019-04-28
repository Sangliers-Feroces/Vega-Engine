/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static void chunk_set_terrain(chunk_t *chunk)
{
    if (chunk->terrain != NULL)
        return;
    chunk_gen_terrain(chunk->pos);
    for (size_t i = 0; i < 1; i++) {
    entity3 *ent = world_add_entity();
    ent->trans.is_static = 0;
    ent->trans.is_physics = 1;
    ent->trans.pos = dvec3_init(200.0, 64.0, 200.0);
    ent->trans.scale = dvec3_init(0.1, 0.1, 0.1);
    ent->trans.rot = dvec3_init(M_PI / 2.0, 0.0, 0.0);
    ent->trans.speed = dvec3_init(5.0, randf() * 5.0 - 2.5, 2.0);


    mesh_full_t *mesh;
    vec3 base = {0.0, -42.0f, 0.0};
    vec3 sq[4];
    vec2 uv[3] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 1.0f}};

    sq[0] = base;
    sq[1] = vec3_add(base, (vec3){CHUNK_SIZE, 0.0f, 0.0f});
    sq[2] = vec3_add(base, (vec3){0.0f, 0.0f, CHUNK_SIZE});
    sq[3] = vec3_add(base, (vec3){CHUNK_SIZE, 0.0f, CHUNK_SIZE});
    mesh = entity3_create_render(ent, 0, MATERIAL_WATER, 0);
    mesh_add_triangle_pos_uv(mesh->mesh, (vec3[]){sq[0], sq[2], sq[1]}, uv);
    mesh_add_triangle_pos_uv(mesh->mesh, (vec3[]){sq[3], sq[1], sq[2]}, uv);
    entity3_trans_update(ent);
    entity3_add_trigger(ent,
    trigger_create(dvec3_init(0, -42.0, 0), dvec3_init(256.0, -40.0, 256.0), TRIGGER_ON_HIT_NONE));
    }
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
    entity3_destroy(chunk->ents_global);
    free(chunk);
}
