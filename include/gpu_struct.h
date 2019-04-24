/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** vulkan ftw
*/

#pragma once

typedef enum {
    SHADER_WORLD,
    SHADER_WATER,
    SHADER_FONT,
    SHADER_IU,
    SHADER_MAX
} shader_t;

typedef struct {
    gluint program;
    gluint uniform[16];
} shader_cache_t;

typedef enum {
    MATERIAL_GRASS,
    MATERIAL_WATER,
    MATERIAL_MAX
} material_t;

typedef struct {
    void (*world)(dmat4 mvp, dmat4 world, dmat4 rot);
    void (*entity)(dmat4 mvp, dmat4 world, dmat4 rot);
    int is_transparent;
} material_full_t;

typedef struct {
    shader_t shader;
    const char *vertex;
    const char *fragment;
    int is_standard;
} shader_desc_t;

typedef struct {
    material_t material;
    void (*world)(dmat4 mvp, dmat4 world, dmat4 rot);
    void (*entity)(dmat4 mvp, dmat4 world, dmat4 rot);
    int is_transparent;
} material_desc_t;

typedef struct {
    material_t material;
    dmat4_w mvp;
    dmat4_w world;
    dmat4_w rot;
    gluint vertex_array;
    size_t count;
} render_call_t;

typedef struct {
    size_t count;
    size_t allocated;
    render_call_t *call;
} vec_render_call_t;
