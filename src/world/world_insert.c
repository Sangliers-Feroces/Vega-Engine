/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static void world_chunk_flush_inserting(void)
{
    for (size_t i = 0; i < _demo->world.chunk_count; i++)
        _demo->world.chunk[i]->inserting = NULL;
}

void world_insert_start(void)
{
    world_chunk_flush_inserting();
}

void world_insert_end(size_t lod_collision)
{
    if (lod_collision != ~0ULL)
        for (size_t i = 0; i < _demo->world.chunk_count; i++)
            if (_demo->world.chunk[i]->inserting != NULL) {
                entity3_set_col(_demo->world.chunk[i]->inserting,
                _demo->world.chunk[i]->inserting->render[lod_collision].mesh->mesh);
            }
    world_chunk_flush_inserting();
}

static void insert_data(mesh_full_t *src, mesh_full_t *dst, vec3 *pos, size_t i)
{
    if (!src->has_ext) {
        for (size_t j = 0; j < 3; j++)
            mesh_full_add_vertex(dst,
            vertex_init(pos[j], src->mesh->vertex[i * 3 + j].normal,
            src->mesh->vertex[i * 3 + j].uv));
    } else {
        for (size_t j = 0; j < 3; j++)
            mesh_full_add_vertex_ext(dst,
            vertex_init(pos[j], src->mesh->vertex[i * 3 + j].normal,
            src->mesh->vertex[i * 3 + j].uv),
            src->ext[i * 3 + j]);
    }
}

static void insert_triangle(mesh_full_t *mesh, size_t i,
material_t material, size_t lod)
{
    vec3 pos[3];
    chunk_t *chunk;

    for (size_t j = 0; j < 3; j++)
        pos[j] = mesh->mesh->vertex[i * 3 + j].pos;
    chunk = world_chunk_get_by_pos(vec3_dvec3(pos[0]));
    for (size_t j = 0; j < 3; j++)
            pos[j] = vec3_sub(pos[j], dvec3_vec3(chunk->ents->trans.pos));
    if (chunk->inserting == NULL) {
        chunk->inserting = chunk_add_entity(chunk);
        entity3_create_render(chunk->inserting, lod, material, 0);
    }
    insert_data(mesh, chunk->inserting->render[lod].mesh, pos, i);
}

void world_insert_mesh(mesh_full_t *mesh, material_t material, size_t lod)
{
    size_t count = mesh->mesh->vertex_count / 3;

    for (size_t i = 0; i < count; i++)
        insert_triangle(mesh, i, material, lod);
}

void world_insert_arr_dvec3(arr_dvec3_t arr, material_t material, size_t lod)
{
    mesh_full_t *mesh = mesh_full_create(0, 0);
    vec3 pos[3];
    vec3 normal;
    vec2 uv[3] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 1.0f}};
    size_t count = arr.count / 3;

    for (size_t i = 0; i < count; i++) {
        for (size_t j = 0; j < 3; j++)
            pos[j] = dvec3_vec3(arr.dvec3[i * 3 + j]);
        normal = normal3(pos[0], pos[1], pos[2]);
        for (size_t j = 0; j < 3; j++)
            mesh_full_add_vertex(mesh, vertex_init(pos[j], normal, uv[j]));
    }
    world_insert_mesh(mesh, material, lod);
    mesh_full_destroy(mesh);
}
