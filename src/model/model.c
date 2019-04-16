/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

model_t* model_create(const vertex_serial_t *vertex, size_t vertex_count,
texture2 *texture)
{
    model_t *res = (model_t*)malloc_safe(sizeof(model_t));
    dvec3 norm;

    (void)norm;
    (void)vertex;
    if ((vertex_count % 3) != 0)
        return NULL;
    res->texture = texture;
    res->vertex = (vertex_t*)malloc_safe(vertex_count * sizeof(vertex_t));
    for (size_t i = 0; i < vertex_count; i++) {
        //if ((i % 3) == 0)
        //    norm = normal3(vertex[i].pos, vertex[i + 4].pos, vertex[i + 2].pos);
        //res->vertex[i] = (vertex_t){vertex[i].pos, norm, vertex[i].uv};
    }
    res->vertex_count = vertex_count;
    glGenBuffers(1, &res->buffer);
    glBindBuffer(GL_ARRAY_BUFFER, res->buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_t) * res->vertex_count,
    res->vertex, GL_STATIC_DRAW);
    return (res);
}

void model_destroy(model_t *model)
{
    glDeleteBuffers(1, &model->buffer);
    free(model->vertex);
    free(model);
}

entity_t* entity_create(model_t *model)
{
    entity_t *res = (entity_t*)malloc_safe(sizeof(entity_t));

    res->pos = (dvec3){0.0f, 0.0f, 0.0f};
    res->rot = (dvec3){0.0f, 0.0f, 0.0f};
    res->scale = (dvec3){1.0f, 1.0f, 1.0f};
    res->model = model;
    mat4_identity(res->trans);
    res->vertex =
    (vertex_t*)malloc_safe(model->vertex_count * sizeof(vertex_t));
    return res;
}

void entity_destroy(entity_t *entity)
{
    free(entity->vertex);
    free(entity);
}
