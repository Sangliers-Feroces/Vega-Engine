/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#pragma once

void world_insert_vec_rtx_triangle(demo_t *demo, vec_rtx_triangle vec);

void world_init(demo_t *demo);
void world_quit(demo_t *demo);

chunk_t** world_chunk2d_get(demo_t *demo, ssize2 pos);
void world_chunk2d_insert(demo_t *demo, chunk_t *chunk);
chunk_t* world_chunk_get(demo_t *demo, ssize2 pos);
chunk_t* world_chunk_get_by_pos(demo_t *demo, vec3 pos);

chunk_t* chunk_create(ssize2 pos);
void chunk_destroy(chunk_t *chunk);
void chunk_insert_rtx_triangle(chunk_t *chunk, rtx_triangle *triangle);
void chunk_insert_rtx_triangle_lod(chunk_t *chunk, size_t lod,
rtx_triangle *triangle);

chunk_lod_t chunk_lod_create(chunk_t *par);
void chunk_lod_destroy(chunk_lod_t lod);
void chunk_lod_insert_rtx_triangle(chunk_lod_t *lod, rtx_triangle *triangle);

void world_render(demo_t *demo);

vec_chunk_vertex_t vec_chunk_vertex_create(size_t count);
void vec_chunk_vertex_destroy(vec_chunk_vertex_t vec);
void chunk_lod_reupload_buf(chunk_lod_t *lod);

void chunk_gen_terrain(chunk_t *chunk);

chunk_border_t chunk_border_fetch(ssize2 pos);

void world_chunk_god(demo_t *demo);
