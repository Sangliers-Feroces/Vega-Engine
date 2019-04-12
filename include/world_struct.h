/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#pragma once

#define WORLD_LOD_COUNT 1

typedef struct {
    octree *tree;
    gluint vertex_buffer;
    int do_reupload_buf;
} chunk_lod_t;

typedef struct {
    ssize2 pos;
    size_t lod_count;
    chunk_lod_t lod[WORLD_LOD_COUNT];
    size_t world_ndx;
} chunk_t;

typedef struct {
    size_t chunk_count;
    size_t chunk_allocated;
    chunk_t **chunk;        // used for rendering
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
