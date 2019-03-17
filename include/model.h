/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#ifndef _MODEL_H
#define _MODEL_H

model_t* model_create(const vertex_serial_t *vertex, size_t vertex_count,
texture2 *texture);
void model_destroy(model_t *model);
entity_t* entity_create(model_t *model);
void entity_destroy(entity_t *entity);

void entity_refresh(entity_t * entity);
void entity_draw(demo_t *demo, entity_t *entity);

void vertex_intersect_ray_no_cull(vertex_t *vertex, ray3 ray,
inter_ray3_ent *inter, int authorize_oob);
inter_ray3_ent entity_intersect(entity_t *entity, ray3 ray);

#endif
