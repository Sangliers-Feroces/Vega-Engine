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
} material_desc_t;
