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
#define CHUNK_LOAD_DISTANCE 4

typedef struct {
    size_t lod;
    vec_rtx_triangle *geom;
    size_t vertex_count;
    gluint vertex_buffer;
    gluint vertex_array;
    int do_reupload_buf;
} chunk_lod_t;

typedef struct {
    arr_dvec3_t hor[CHUNK_GEN_ITER][2];  // negative x, then positive
    arr_dvec3_t ver[CHUNK_GEN_ITER][2];  // negative z, then positive
} chunk_border_t;

typedef struct {
    ssize2 pos;
    size_t lod_count;
    chunk_lod_t lod[WORLD_LOD_COUNT];
    size_t world_ndx;
    chunk_border_t border;
} chunk_t;

typedef struct {
    size_t chunk_count;
    size_t chunk_allocated;
    chunk_t **chunk;        // used for rendering / world intersection
    srect chunk2d_area;
    chunk_t **chunk2d;      // 2d array for fast lookup
    octree *tree;           // collision data is exclusively stored here
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

typedef struct {
    dvec3 pos;
    dvec3 normal;
    vec2 uv_albedo;
    vec2 uv_lightmap;
} chunk_dvertex_t;

typedef struct {
    size_t count;
    chunk_dvertex_t *dvertex;
} vec_chunk_dvertex_t;
