/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static void octree_replace_triangles(demo_t *demo, octree *tree)
{
    if (tree == NULL)
        return;
    for (size_t i = 0; i < 8; i++)
        octree_replace_triangles(demo, tree->sub[i]);
    for (size_t i = 0; i < tree->triangles.count; i++)
        if (!is_triangle_in_bounds(tree->triangles.triangle[i]->vertex,
        tree->bounds)) {
            rtx_triangle_replace(demo, tree, tree->triangles.triangle[i]);
            i--;
            return;
        }
}

void editor_grab_replace(demo_t *demo)
{
    octree_replace_triangles(demo, demo->tree);
}
