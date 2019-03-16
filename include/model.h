/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#ifndef _MODEL_H
#define _MODEL_H

model_t* model_create(const vertex_t *vertex, size_t vertex_count,
texture2 *texture);
void model_destroy(model_t *model);
entity_t* entity_create(model_t *model);
void entity_destroy(entity_t *entity);

void entity_draw(demo_t *demo, entity_t *entity);

#endif
