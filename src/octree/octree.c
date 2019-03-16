/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** optiiiiiii rtx
*/

#include "headers.h"

octree* octree_create_node(octree *root, bounds3 bounds)
{
    octree *res = malloc_safe(sizeof(octree));

    res->root = root;
    for (size_t i = 0; i < 8; i++)
        res->sub[i] = NULL;
    res->triangles.count = 0;
    res->triangles.allocated = 0;
    res->triangles.triangle = NULL;
    res->bounds = bounds;
    return res;
}

octree* octree_create(octree *root)
{
    octree *res = malloc_safe(sizeof(octree));

    res->root = root;
    for (size_t i = 0; i < 8; i++)
        res->sub[i] = NULL;
    res->triangles.count = 0;
    res->triangles.allocated = 0;
    res->triangles.triangle = NULL;
    res->bounds = (bounds3){{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 1.0f};
    return res;
}

void octree_rtx_triangle_free(octree *tree, rtx_triangle *triangle)
{
    size_t ndx = ~0ULL;

    for (size_t i = 0; i < tree->triangles.count; i++)
        if (tree->triangles.triangle[i] == triangle) {
            ndx = i;
            break;
        }
    if (ndx == ~0ULL)
        return;
    rtx_triangle_destroy(triangle);
    tree->triangles.count--;
    for (size_t i = ndx; i < tree->triangles.count; i++)
        tree->triangles.triangle[i] = tree->triangles.triangle[i + 1];
}

void octree_destroy(octree **root)
{
    for (size_t i = 0; i < 8; i++)
        if ((*root)->sub[i] != NULL)
            octree_destroy(&((*root)->sub[i]));
    vec_rtx_triangle_destroy((*root)->triangles);
    free(*root);
    *root = NULL;
}
