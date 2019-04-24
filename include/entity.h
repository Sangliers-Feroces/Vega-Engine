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
void render_obj_destroy(render_obj_t render);
vec_entity3_t vec_entity3_create(void);
size_t vec_entity3_add(vec_entity3_t *vec, entity3 *entity);
void vec_entity3_destroy(vec_entity3_t vec);
entity3* entity3_create_pos(entity3 *parent, dvec3 pos);
entity3* entity3_create(entity3 *parent);
void entity3_set_col(entity3 *ent, int is_on);
void entity3_bind_col(entity3 *entity, mesh_full_ref_t collision_mesh);
void entity3_destroy(entity3 *entity);
entity3* chunk_add_entity(chunk_t *chunk);
void entity3_set_render(entity3 *ent, size_t lod, mesh_full_ref_t mesh,
material_t material);
mesh_full_t* entity3_create_render(entity3 *ent, size_t lod,
material_t material, int has_ext);

void entity3_render(entity3 *ent, dmat4 vp);

vec_render_call_t vec_render_call_init(void);
void vec_render_call_add(vec_render_call_t *vec, render_call_t to_add);
void vec_render_call_flush(vec_render_call_t *vec);
void vec_render_call_destroy(vec_render_call_t vec);
void render_delay_call(render_call_t to_draw);
void render_delay_exec(void);

void entity3_trans_update_model(entity3 *ent);
void entity3_update_solo(entity3 *ent, dmat4 par_world, dmat4 par_rot);
void entity3_update(entity3 *ent);

trigger_t* trigger_create(dvec3 size,
void (*on_hit)(entity3 *ent, entity3 *other));
vec_trigger_t vec_trigger_init(void);
void vec_trigger_add(vec_trigger_t *vec, trigger_t *trigger);
void vec_trigger_destroy(vec_trigger_t vec);
