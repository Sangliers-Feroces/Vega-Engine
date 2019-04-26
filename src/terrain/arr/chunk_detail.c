/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static void split(chunk_t *chunk, arr2d_dvec3_t *arr, chunk_border_t border)
{
    dvec3 chunk_rel = dvec3_init(0.0, 0.0, 0.0);
    arr2d_dvec3_t n;

    for (size_t i = 0; i < CHUNK_GEN_EXT_ITER; i++) {
        terrain_split(arr, 0.05 / (i + 1));
        terrain_apply_constraints(*arr, border, i);
        terrain_send_iter_to_chunk_border(chunk, *arr, i);
        switch (i) {
        case 1:
            n = terrain_gen_normals(*arr);
            terrain_send_ter_to_chunk_lod_gen(chunk, WORLD_LOD_MAX,
            (terrain_send_ter_arg){*arr, n,
            (srect){{0, 0}, {arr->w, arr->h}}}, chunk_rel);
            arr2d_dvec3_destroy(n);
            break;
        }
    }
}

void chunk_detail_terrain(chunk_t *chunk)
{
    arr2d_dvec3_t arr = arr2d_dvec3_copy(chunk->terrain_base);
    chunk_border_t border = chunk_border_fetch(chunk->pos);

    split(chunk, &arr, border);
    arr2d_dvec3_destroy(arr);
    chunk_border_destroy(border);
    entity3_bind_col(chunk->terrain,
    entity3_get_lod_ref(chunk->terrain, WORLD_LOD_MAX));
}
