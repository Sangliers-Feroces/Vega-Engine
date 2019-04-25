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

static void misc(void)
{
    ssize2 p = {0, 0};
    chunk_t *chunk = world_chunk_get(p);

    if (chunk->terrain != NULL) {
        if (chunk->terrain->sub.count > 0) {
            chunk->terrain->trans.rot.y += 0.005;
            chunk->terrain->sub.ent[0]->trans.rot.y -= 0.001;
            chunk->terrain->sub.ent[0]->trans.rot.x -= 0.001;
            return;
        }
        chunk->terrain->trans.is_static = 0;
        chunk->terrain->trans.pos = dvec3_init(16.0, 32.0, -2.0);
        entity3 *ent = entity3_create(chunk->terrain);
        ent->trans.is_static = 0;
        entity3_set_render(ent, 0, entity3_get_lod_ref(chunk->terrain, 1), MATERIAL_GRASS);
        ent->trans.pos = dvec3_init(16.0, 8.0, 0.0);
        ent->trans.scale = dvec3_init(0.1, 1.0, 0.15);
    }
}

void world_update(void)
{
    misc();
    for (size_t i = 0; i < _demo->world.chunk_count; i++)
        chunk_update(_demo->world.chunk[i]);
    entity3_global_update(_demo->world.ents);
    refresh_vp(_demo);
    world_chunk_god();
}
