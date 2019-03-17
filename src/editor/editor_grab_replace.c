/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static int is_point_selected(demo_t *demo, vec3 p)
{
    for (size_t i = 0; i < demo->editor.selections.count; i++)
        if (vec3_eq(demo->editor.selections.selection[i], p))
            return 1;
    return 0;
}

static int is_triangle_selected(demo_t *demo, rtx_triangle *triangle)
{
    for (size_t i = 0; i < 3; i++)
        if (is_point_selected(demo, triangle->vertex[i])) 
            return 1;
    return 0;
}

static void octree_replace_triangles(demo_t *demo, octree *tree)
{
    if (tree == NULL)
        return;
    for (size_t i = 0; i < 8; i++)
        octree_replace_triangles(demo, tree->sub[i]);
    for (size_t i = 0; i < tree->triangles.count; i++)
        if (is_triangle_selected(demo, tree->triangles.triangle[i])) {
            rtx_triangle_replace(demo, tree, tree->triangles.triangle[i]);
            i--;
        }
}

void editor_grab_replace(demo_t *demo)
{
    octree_replace_triangles(demo, demo->tree);
}
