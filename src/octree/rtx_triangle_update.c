/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** optiiiiiii rtx
*/

#include "headers.h"

void lightmap_fill(rect_t rect, float value)
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

void rtx_triangle_update(rtx_triangle *triangle)
{
    texture2f_binding_destroy(triangle->lightmap);
    triangle->lightmap = texture2f_binding_create(triangle->vertex);
    lightmap_fill(triangle->lightmap.alloc->rect, _lightmaps.aperture);
    rtx_triangle_update_tangent(triangle);
}

void rtx_triangle_replace(demo_t *demo, octree *node, rtx_triangle *triangle)
{
    octree_rtx_triangle_detach(node, triangle);
    octree_insert_triangle(&demo->tree, triangle);
}

void rtx_triangle_update_tangent(rtx_triangle *triangle)
{
    triangle->normal =
    normal3(triangle->vertex[0], triangle->vertex[1], triangle->vertex[2]);
    triangle->tangent =
    vec3_normalize(vec3_sub(triangle->vertex[1], triangle->vertex[0]));
    triangle->bitangent = normal3((vec3){0.0f, 0.0f, 0.0f},
    triangle->tangent, triangle->normal);
    triangle->data = 0;
}

rtx_triangle* rtx_triangle_create_no_lightmap(vec3 *triangle)
{
    rtx_triangle *res = (rtx_triangle*)malloc_safe(sizeof(rtx_triangle));

    for (size_t i = 0; i < 3; i++)
        res->vertex[i] = triangle[i];
    res->lightmap =
    (texture2f_binding){NULL, {{0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}}, NULL};
    res->albelo = texture2_binding_create(triangle);
    rtx_triangle_update_tangent(res);
    return (res);
}
