/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#pragma once

#define WORLD_LOD_COUNT 3
#define WORLD_LOD_MAX (WORLD_LOD_COUNT - 1)
#define CHUNK_SIZE 1024.0f
#define CHUNK_GEN_ITER 6
#define CHUNK_LOAD_DISTANCE 8

typedef struct {
    octree *tree;
    size_t vertex_count;
    gluint vertex_buffer;
    gluint vertex_array;
    int do_reupload_buf;
} chunk_lod_t;

typedef struct {
    arr_vec3_t hor[CHUNK_GEN_ITER][2];  // negative x, then positive
    arr_vec3_t ver[CHUNK_GEN_ITER][2];  // negative z, then positive
} chunk_border_t;

typedef struct {
    ssize2 pos;
    size_t lod_count;
    chunk_lod_t lod[WORLD_LOD_COUNT];
    size_t world_ndx;
    chunk_border_t border;
    bounds3 bounds;
} chunk_t;

typedef struct {
    size_t chunk_count;
    size_t chunk_allocated;
    chunk_t **chunk;        // used for rendering / world intersection
    srect chunk2d_area;
    chunk_t **chunk2d;      // 2d array for fast lookup
} world_t;

typedef struct {
    vec3 pos;
    vec3 normal;
    vec2 uv_albedo;
    vec2 uv_lightmap;
} chunk_vertex_t;

typedef struct {
    size_t count;
    chunk_vertex_t *vertex;
} vec_chunk_vertex_t;
