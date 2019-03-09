/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** optiiiiiii rtx
*/

#include "headers.h"

void octree_reset_lumels(octree *tree)
{
    if (tree == NULL)
        return;
    for (size_t i = 0; i < tree->triangles.count; i++)
        texture2f_reset(tree->triangles.triangle[i].lumels);
    for (size_t i = 0; i < 8; i++)
        octree_reset_lumels(tree->sub[i]);
}

static float octree_get_max_lumel_actual(octree *tree, float cur)
{
    float max;

    if (tree == NULL)
        return cur;
    for (size_t i = 0; i < tree->triangles.count; i++) {
        max = texture2f_get_max_lumel(tree->triangles.triangle[i].lumels);
        if (max > cur)
            cur = max;
    }
    for (size_t i = 0; i < 8; i++)
        cur = octree_get_max_lumel_actual(tree->sub[i], cur);
    return cur;
}

float octree_get_max_lumel(octree *tree)
{
    return octree_get_max_lumel_actual(tree, 0.0f);
}

void octree_update_lightmap(octree *tree, float max_lumel)
{
    if (tree == NULL)
        return;
    for (size_t i = 0; i < tree->triangles.count; i++)
        texture_update_lightmap(tree->triangles.triangle[i].lumels,
        tree->triangles.triangle[i].lightmap.texture, max_lumel);
    for (size_t i = 0; i < 8; i++)
        octree_update_lightmap(tree->sub[i], max_lumel);
}
