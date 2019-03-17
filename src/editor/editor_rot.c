/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static void rot_vec2(vec2 *to_flip)
{
    vec2 buf = to_flip[0];

    for (size_t i = 0; i < 2; i++)
        to_flip[i] = to_flip[i + 1];
    to_flip[2] = buf;
}

static void rtx_triangle_rot(rtx_triangle *triangle)
{
    rot_vec2(triangle->albelo.uv);
}

static void rot_rec(demo_t *demo, octree *tree)
{
    if (tree == NULL)
        return;
    for (size_t i = 0; i < 8; i++)
        rot_rec(demo, tree->sub[i]);
    for (size_t i = 0; i < tree->triangles.count; i++)
        if (rtx_triangle_is_selected(demo, tree->triangles.triangle[i]))
            rtx_triangle_rot(tree->triangles.triangle[i]);
}

void editor_rot(demo_t *demo)
{
    rot_rec(demo, demo->tree);
}
