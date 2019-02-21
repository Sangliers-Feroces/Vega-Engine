/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** optiiiiiii rtx
*/

#include "headers.h"

void octree_light_rtx(octree *tree, size_t rays)
{
    float max;

    octree_reset_lumels(tree);
    octree_update_lightmap(tree, MAX(octree_get_max_lumel(tree), 1.0f) / 3.0f);
}
