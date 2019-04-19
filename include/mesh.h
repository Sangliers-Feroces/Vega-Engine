/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#pragma once

mesh_t* mesh_create(size_t vertex_count, int gpu_do_upload);
void mesh_destroy(mesh_t *mesh);
void mesh_add_vertex(mesh_t *mesh, vertex_t vertex);
void mesh_add_triangle(mesh_t *mesh, vertex_t *triangle);
void mesh_add_triangle_pos_uv(mesh_t *mesh, vec3 *pos, vec2 *uv);
mesh_full_t* mesh_full_create(size_t vertex_count, int gpu_do_upload,
int has_ext);
void mesh_full_destroy(mesh_full_t *mesh);
void mesh_full_ensure_coherence(mesh_full_t *mesh);
void mesh_full_add_vertex(mesh_full_t *mesh, vertex_t vertex);
void mesh_full_add_vertex_ext(mesh_full_t *mesh, vertex_t vertex,
vertex_ext_t ext);

vertex_t vertex_init(vec3 pos, vec3 normal, vec2 uv);

vec_rtx_triangle_ref vec_rtx_triangle_ref_create(size_t count);
vec_rtx_triangle_ref vec_rtx_triangle_ref_get_void(void);
void vec_rtx_triangle_ref_destroy(vec_rtx_triangle_ref vec);
transform_t transform_get_default(void);
col_ref_t col_ref_get_default(void);
render_obj_t render_obj_get_default(void);
vec_entity3_t vec_entity3_create(void);
size_t vec_entity3_add(vec_entity3_t *vec, entity3 *entity);
void vec_entity3_destroy(vec_entity3_t vec);
entity3* entity3_create(entity3 *parent);
void entity3_destroy(entity3 *entity);
entity3* chunk_entity_add(chunk_t *chunk);
void entity_set_col(entity3 *entity, mesh_t *collision_mesh);
