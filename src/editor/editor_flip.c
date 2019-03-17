/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static int rtx_triangle_should_flip(demo_t *demo, rtx_triangle *triangle)
{
    for (size_t i = 0; i < 3; i++)
        if (!editor_is_point_selected(demo, triangle->vertex[i]))
            return 0;
    return 1;
}

static void flip_vec2(vec2 *to_flip)
{
    vec2 buf = to_flip[0];

    to_flip[0] = to_flip[1];
    to_flip[1] = buf;
}

static void rtx_triangle_flip(rtx_triangle *triangle)
{
    vec3 buf = triangle->vertex[0];

    triangle->vertex[0] = triangle->vertex[1];
    triangle->vertex[1] = buf;
    flip_vec2(triangle->albelo.uv);
    rtx_triangle_update(triangle);
}

static void flip_rec(demo_t *demo, octree *tree)
{
    if (tree == NULL)
        return;
    for (size_t i = 0; i < 8; i++)
        flip_rec(demo, tree->sub[i]);
    for (size_t i = 0; i < tree->triangles.count; i++)
        if (rtx_triangle_should_flip(demo, tree->triangles.triangle[i]))
            rtx_triangle_flip(tree->triangles.triangle[i]);
}

void editor_flip(demo_t *demo)
{
    flip_rec(demo, demo->tree);
}
