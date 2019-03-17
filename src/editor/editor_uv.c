/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static void uv_vec2(vec2 *to_flip)
{
    vec2 origin = {0.0f, 0.0f};

    if (vec2_eq(to_flip[0], origin)) {
        to_flip[0] = (vec2){1.0f, 0.0f};
        to_flip[1] = (vec2){1.0f, 1.0f};
        to_flip[2] = (vec2){0.0f, 1.0f};
    } else {
        to_flip[0] = (vec2){0.0f, 0.0f};
        to_flip[1] = (vec2){1.0f, 0.0f};
        to_flip[2] = (vec2){0.0f, 1.0f};
    }
}

static void rtx_triangle_uv(rtx_triangle *triangle)
{
    uv_vec2(triangle->albelo.uv);
}

static void uv_rec(demo_t *demo, octree *tree)
{
    if (tree == NULL)
        return;
    for (size_t i = 0; i < 8; i++)
        uv_rec(demo, tree->sub[i]);
    for (size_t i = 0; i < tree->triangles.count; i++)
        if (rtx_triangle_is_selected(demo, tree->triangles.triangle[i]))
            rtx_triangle_uv(tree->triangles.triangle[i]);
}

void editor_uv(demo_t *demo)
{
    uv_rec(demo, demo->tree);
}
