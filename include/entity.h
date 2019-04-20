/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** sanic
*/

#pragma once

vec_rtx_triangle_ref vec_rtx_triangle_ref_create(size_t count);
vec_rtx_triangle_ref vec_rtx_triangle_ref_get_void(void);
void vec_rtx_triangle_ref_destroy(vec_rtx_triangle_ref vec);
transform_t transform_get_default(void);
col_ref_t col_ref_get_default(void);
render_obj_t render_obj_get_default(void);
vec_entity3_t vec_entity3_create(void);
size_t vec_entity3_add(vec_entity3_t *vec, entity3 *entity);
void vec_entity3_destroy(vec_entity3_t vec);
entity3* entity3_create_pos(entity3 *parent, dvec3 pos);
entity3* entity3_create(entity3 *parent);
void entity3_destroy(entity3 *entity);
entity3* chunk_entity_add(chunk_t *chunk);
void entity_set_col(entity3 *entity, mesh_t *collision_mesh);

void entity3_render(entity3 *ent, dmat4 vp);

void entity_trans_update_model(entity3 *ent);
void entity3_update(entity3 *ent);