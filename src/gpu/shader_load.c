/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** vulkan ftw
*/

#include "headers.h"

const shader_desc_t shader_desc[] = {
    {SHADER_WORLD, "src/shader/world_vertex.glsl",
    "src/shader/world_fragment.glsl", 1, 0},
    {SHADER_WATER, "src/shader/world_vertex.glsl",
    "src/shader/water_fragment.glsl", 1, 0},
    {SHADER_FONT, "src/shader/font_vertex.glsl",
    "src/shader/font_fragment.glsl", 0, 0},
    {SHADER_IU, "src/shader/ui_vertex.glsl",
    "src/shader/ui_fragment.glsl", 0, 0},
    {SHADER_HDR, "src/shader/hdr_vertex.glsl",
    "src/shader/hdr_fragment.glsl", 0, 0},
    {SHADER_SKYBOX, "src/shader/skybox_vertex.glsl",
    "src/shader/skybox_fragment.glsl", 1, 0},
    {SHADER_VEG, "src/shader/veg_vertex.glsl",
    "src/shader/veg_fragment.glsl", 1, 1},
    {0, NULL, NULL, 0, 0}
};

const material_desc_t mat_desc[] = {
    {MATERIAL_GRASS, &material_fun_grass_world, &material_fun_grass_entity, 0},
    {MATERIAL_WATER, &material_fun_water_world, &material_fun_water_entity, 1},
    {MATERIAL_SKYBOX, &material_fun_skybox_world,
    &material_fun_skybox_entity, 1},
    {MATERIAL_VEG_GRASS1, &material_fun_veg_grass1_entity,
    &material_fun_veg_grass1_entity, 0},
    {0, NULL, NULL, 0}
};

static void shader_load_nstandard_uniform(
shader_desc_t desc, shader_cache_t *res)
{
    switch (desc.shader) {
    case SHADER_FONT:
        res->uniform[0] = glGetUniformLocation(res->program, "tex_pos");
        res->uniform[1] = glGetUniformLocation(res->program, "tex_size");
        res->uniform[2] = glGetUniformLocation(res->program, "pos");
        res->uniform[3] = glGetUniformLocation(res->program, "size");
        res->uniform[4] = glGetUniformLocation(res->program, "depth");
        break;
    case SHADER_IU:
        res->uniform[0] = glGetUniformLocation(res->program, "pos");
        res->uniform[1] = glGetUniformLocation(res->program, "size");
        res->uniform[2] = glGetUniformLocation(res->program, "depth");
        break;
    case SHADER_HDR:
        res->uniform[0] = glGetUniformLocation(res->program, "p_cam");
        res->uniform[1] = glGetUniformLocation(res->program, "t");
        break;
    default:
        break;
    }
}

static void shader_load_pstandard_uniform(
shader_desc_t desc, shader_cache_t *res)
{
    switch (desc.shader) {
    case SHADER_VEG:
        res->uniform[3] = glGetUniformLocation(res->program, "off");
        break;
    default:
        break;
    }
}

static shader_cache_t get_shader(shader_desc_t desc)
{
    shader_cache_t res = {0, 1, {0}};

    res.program = shader_load_vert_frag(desc.vertex, desc.fragment);
    res.do_cull = desc.do_cull;
    if (desc.is_standard) {
        res.uniform[0] = glGetUniformLocation(res.program, "mvp");
        res.uniform[1] = glGetUniformLocation(res.program, "world");
        res.uniform[2] = glGetUniformLocation(res.program, "rot");
    } else
        shader_load_nstandard_uniform(desc, &res);
    shader_load_pstandard_uniform(desc, &res);
    return res;
}

void shader_init(demo_t *demo)
{
    for (size_t i = 0; i < SHADER_MAX; i++)
        demo->shader[i].program = 0;
    for (size_t i = 0; shader_desc[i].vertex != NULL; i++)
        demo->shader[shader_desc[i].shader] = get_shader(shader_desc[i]);
    for (size_t i = 0; i < SHADER_MAX; i++)
        if (demo->shader[i].program == 0) {
            printf("Error: can't load shader #%zu.\n", i);
            exit(84);
        }
}

void shader_quit(demo_t *demo)
{
    for (size_t i = 0; i < SHADER_MAX; i++)
        glDeleteProgram(demo->shader[i].program);
}

void material_init(demo_t *demo)
{
    for (size_t i = 0; i < MATERIAL_MAX; i++)
        demo->material[i] = (material_full_t){NULL, NULL, 0};
    for (size_t i = 0; mat_desc[i].world != NULL; i++)
        demo->material[mat_desc[i].material] =
        (material_full_t){mat_desc[i].world, mat_desc[i].entity,
        mat_desc[i].is_transparent};
    for (size_t i = 0; i < MATERIAL_MAX; i++)
        if (demo->material[i].entity == NULL) {
            printf("Error: can't load material #%zu.\n", i);
            exit(84);
        }
}
