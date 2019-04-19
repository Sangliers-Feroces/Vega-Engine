/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** vulkan ftw
*/

#include "headers.h"

const shader_desc_t shader_desc[] = {
    {SHADER_WORLD, "src/shader/world_vertex.glsl",
    "src/shader/world_fragment.glsl"},
    {SHADER_WATER, "src/shader/world_vertex.glsl",
    "src/shader/water_fragment.glsl"},
    {SHADER_FONT, "src/gpu/shader/ui_vertex.glsl",
    "src/shader/font_fragment.glsl"},
    {0, NULL, NULL}
};

const material_desc_t mat_desc[] = {
    {MATERIAL_GRASS, &material_fun_grass_world, &material_fun_grass_entity},
    {MATERIAL_WATER, &material_fun_water_world, &material_fun_water_entity},
    {0, NULL, NULL}
};

void shader_init(demo_t *demo)
{
    for (size_t i = 0; i < SHADER_MAX; i++)
        demo->shader[i] = 0;
    for (size_t i = 0; shader_desc[i].vertex != NULL; i++)
        demo->shader[shader_desc[i].shader] =
        shader_load_vert_frag(shader_desc[i].vertex, shader_desc[i].fragment);
    for (size_t i = 0; i < SHADER_MAX; i++)
        if (demo->shader[i] == 0) {
            printf("Error: can't load shader #%zu.\n", i);
            exit(84);
        }
}

void shader_quit(demo_t *demo)
{
    for (size_t i = 0; i < SHADER_MAX; i++)
        glDeleteProgram(demo->shader[i]);
}

void material_init(demo_t *demo)
{
    for (size_t i = 0; i < MATERIAL_MAX; i++)
        demo->material[i] = (material_full_t){NULL, NULL};
    for (size_t i = 0; mat_desc[i].world != NULL; i++)
        demo->material[mat_desc[i].material] =
        (material_full_t){mat_desc[i].world, mat_desc[i].entity};
    for (size_t i = 0; i < MATERIAL_MAX; i++)
        if (demo->material[i].world == NULL) {
            printf("Error: can't load material #%zu.\n", i);
            exit(84);
        }
}
