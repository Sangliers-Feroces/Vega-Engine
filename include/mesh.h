/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#pragma once

mesh_t* mesh_create(int gpu_do_upload);
void mesh_destroy(mesh_t *mesh);
void mesh_add_vertex(mesh_t *mesh, vertex_t vertex);
void mesh_add_triangle(mesh_t *mesh, vertex_t *triangle);
void mesh_add_triangle_pos_uv(mesh_t *mesh, vec3 *pos, vec2 *uv);
void mesh_full_add_triangle_pos_uv(mesh_full_t *mesh, vec3 *pos, vec2 *uv);
mesh_full_t* mesh_full_create(int gpu_do_upload, int has_ext);
void mesh_full_destroy(mesh_full_t *mesh);
void mesh_full_ensure_coherence(mesh_full_t *mesh);
void mesh_full_add_vertex(mesh_full_t *mesh, vertex_t vertex);
void mesh_full_add_vertex_ext(mesh_full_t *mesh, vertex_t vertex,
vertex_ext_t ext);

vec_mesh_full_t vec_mesh_full_init(void);
void vec_mesh_full_add(vec_mesh_full_t *vec, mesh_full_t *to_add);
void vec_mesh_full_destroy(vec_mesh_full_t vec);
void chunk_add_mesh(chunk_t *chunk, mesh_full_t *mesh);

vertex_t vertex_init(vec3 pos, vec3 normal, vec2 uv);
