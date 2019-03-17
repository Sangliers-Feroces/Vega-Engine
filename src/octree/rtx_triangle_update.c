/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** optiiiiiii rtx
*/

#include "headers.h"

static void fill_lightmap(rect_t rect, float value)
{
    ivec2 start = {rect.p.x * (float)_lightmaps.base->w,
    rect.p.y * (float)_lightmaps.base->h};
    ivec2 size = {rect.s.x * (float)_lightmaps.base->w,
    rect.s.y * (float)_lightmaps.base->h};
    vec4 to_fill = {value, value, value, 0.0f};

    for (int i = 0; i < size.y; i++)
        for (int j = 0; j < size.x; j++)
            _lightmaps.base->pixel[
            (start.y + i) * _lightmaps.base->w + (start.x + j)] = to_fill;
}

void rtx_triangle_update(demo_t *demo, rtx_triangle *triangle)
{
    texture2f_binding_destroy(triangle->lightmap);
    triangle->lightmap = texture2f_binding_create(triangle->vertex);
    fill_lightmap(triangle->lightmap.alloc->rect, demo->cam.aperture);
    triangle->normal =
    normal3(triangle->vertex[0], triangle->vertex[1], triangle->vertex[2]);
    triangle->tangent =
    vec3_normalize(vec3_sub(triangle->vertex[1], triangle->vertex[0]));
    triangle->bitangent = normal3((vec3){0.0f, 0.0f, 0.0f},
    triangle->tangent, triangle->normal);
}
