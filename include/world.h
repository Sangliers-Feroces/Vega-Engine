/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#pragma once

void world_insert_start(void);
void world_insert_end(size_t lod_collision);
void world_insert_mesh(mesh_full_t *mesh, material_t material, size_t lod);
void world_insert_arr_dvec3(arr_dvec3_t arr, material_t material, size_t lod);

void world_init(demo_t *demo);
void world_quit(demo_t *demo);

chunk_t** world_chunk2d_get(demo_t *demo, ssize2 pos);
void world_chunk2d_insert(demo_t *demo, chunk_t *chunk);
chunk_t* world_chunk_get(demo_t *demo, ssize2 pos);
ssize2 chunk_get_pos(dvec3 pos);
chunk_t* world_chunk_get_by_pos(dvec3 pos);
void chunk_update(chunk_t *chunk);

chunk_t* chunk_create_detached(ssize2 pos);
void chunk_attach(chunk_t *chunk);
chunk_t* chunk_create(ssize2 pos);
void chunk_destroy(chunk_t *chunk);

chunk_lod_t chunk_lod_create(size_t lod);
void chunk_lod_destroy(chunk_lod_t *lod);
void chunk_lod_insert_rtx_triangle(chunk_lod_t *lod, rtx_triangle *triangle);

void world_render(demo_t *demo);

vec_chunk_vertex_t vec_chunk_vertex_create(size_t count);
void vec_chunk_vertex_destroy(vec_chunk_vertex_t vec);
vec_chunk_dvertex_t vec_chunk_dvertex_create(size_t count);
void vec_chunk_dvertex_destroy(vec_chunk_dvertex_t vec);
void chunk_lod_reupload_buf(chunk_lod_t *lod);

void chunk_gen_terrain(chunk_t *chunk, entity3 *ent);

chunk_border_t chunk_border_fetch(ssize2 pos);

void world_chunk_god(demo_t *demo);
