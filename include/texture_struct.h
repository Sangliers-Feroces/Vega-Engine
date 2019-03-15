/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** headers
*/

#ifndef _TEXTURE_STRUCT_H
#define _TEXTURE_STRUCT_H

typedef struct {
    vec2 size;
    int32_t w;
    int32_t h;
    size_t max_ndx;
    uint32_t *pixel;
    gluint id;
} texture2;

typedef struct {
    vec2 size;
    int32_t w;
    int32_t h;
    size_t max_ndx;
    vec4 *pixel;
    gluint id;
} texture2f;

typedef struct {
    size_t row;
    int32_t start;
    int32_t size;
    size_t shared_count;
    rect_t rect;
} texture_cluster_row_alloc;

typedef struct {
    size_t count;
    size_t allocated;
    texture_cluster_row_alloc **cluster_row;    // to keep references safe
} vec_texture_cluster_row_alloc;                // still a normal 1D-array

typedef struct {
    int32_t power;
    int32_t h;
    vec_texture_cluster_row_alloc row_allocs;
} texture_cluster_row;

typedef struct {
    size_t count;
    size_t allocated;
    texture_cluster_row *cluster_row;
} vec_texture_cluster_row;

typedef struct {
    texture2f *base;
    int32_t to_fill_y;
    vec_texture_cluster_row rows;
} texture_cluster;

typedef struct {
    size_t row;
    int32_t power;
    ivec2 size;
} texture_cluster_alloc_info;

typedef struct {
    texture2 *texture;
    vec2 uv[3];
} texture2_binding;    /* the object linked                               */

typedef struct {
    texture2f *texture;
    vec2 uv[3];
    texture_cluster_row_alloc *alloc;
} texture2f_binding;

typedef struct {
    int count;
    texture2 **texture;
} texture_pannel_t;

#endif
