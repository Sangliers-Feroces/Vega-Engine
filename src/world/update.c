/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

void entity3_set_on_ground(entity3 *ent)
{
    dvec3 p = ent->trans.pos;
    inter_ray3 inter = world_inter((ray3){dvec3_init(p.x, 1024.0, p.z),
    dvec3_init(0.0, -1.0, 0.0)});

    ent->trans.pos = dvec3_add(inter.p, dvec3_init(0.0, 1.0, 0.0));
}

static void update_enemy_chunk(chunk_t *chunk)
{
    entity3 *ent;
    entity3_tag_enemy_data_t *data;
    dvec3 p;
    dvec3 n;

    if (chunk->is_stalled)
        return;
    p = dmat4_trans(_demo->world.player->trans.world);
    p.y = 0.0;
    while (chunk->enemy_count < chunk->enemy_count_max) {
        n = dvec3_init(randf() * CHUNK_SIZE, 0.0, randf() * CHUNK_SIZE);
        if (dvec3_dist(p, n) < CHUNK_SIZE / 2.0)
            continue;
        ent = world_add_entity();
        ent->trans.is_physics = 1;
        ent->trans.is_static = 0;
        ent->trans.slide_threshold = 0.85;
        ent->trans.pos = dvec3_add(dmat4_trans(chunk->ents->trans.world),
        dvec3_init(n.x, 1024.0, n.z));
        ent->trans.speed = dvec3_init(0.0, -10.0, 0.0);
        entity3_set_tag(ent, ENTITY3_TAG_ENEMY);
        data = ent->tag_data;
        data->chunk = chunk->pos;
        data->max_speed = 6.0;
        entity3_trans_update(ent);
        entity3_set_on_ground(ent);
        data->spawn = ent->trans.pos;
        entity3_trans_update(ent);
        ent = entity3_create(ent);
        entity3_set_render(ent, 0, mesh_full_ref_bank_init(MESH_BANK_ENEMY1),
        MATERIAL_GRASS);
        ent->trans.scale = dvec3_init(0.04, 0.04, 0.04);
        entity3_trans_update(ent);
        ent->trans.is_static = 0;
        ent->lod_dist = RENDER_OBJ_LOD_DIST_FAR;
        chunk->enemy_count++;
    }
}

static void chunk_update(chunk_t *chunk)
{
    if (chunk->is_stalled)
        return;
    update_enemy_chunk(chunk);
    entity3_update(chunk->ents);
    if (chunk->ents_ext != NULL)
        entity3_update(chunk->ents_ext);
    while (chunk->ents_global->sub.count > 0)
        entity3_move(chunk->ents_global->sub.ent[0], _demo->world.ents);
}

void world_update(void)
{
    world_chunk_god();
    for (size_t i = 0; i < _demo->world.chunk_count; i++)
        chunk_update(_demo->world.chunk[i]);
    entity3_global_update(_demo->world.ents);
    world_update_triggers();
    refresh_vp(_demo);
}
