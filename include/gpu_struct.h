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
    SHADER_MAX
} shader_t;

typedef enum {
    MATERIAL_GRASS,
    MATERIAL_WATER,
    MATERIAL_MAX
} material_t;

typedef struct {
    void (*world)(dmat4 mvp, dmat4 world);
    void (*entity)(dmat4 mvp, dmat4 world);
} material_full_t;

typedef struct {
    shader_t shader;
    const char *vertex;
    const char *fragment;
} shader_desc_t;

typedef struct {
    material_t material;
    void (*world)(dmat4 mvp, dmat4 world);
    void (*entity)(dmat4 mvp, dmat4 world);
} material_desc_t;
