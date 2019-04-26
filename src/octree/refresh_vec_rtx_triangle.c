/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** optiiiiiii rtx
*/

#include "headers.h"

void octree_flush_vec_rtx_triangle(octree *tree)
{
    octree *root;

    if (tree == NULL)
        return;
    if (tree->triangles->count > 0)
        return;
    vec_rtx_triangle_flush(tree->triangles);
    for (size_t i = 0; i < 8; i++)
        if (tree->sub[i] != NULL)
            return;
    root = tree->root;
    if (root == NULL)
        return;
    for (size_t i = 0; i < 8; i++)
        if (root->sub[i] == tree) {
            octree_destroy(&root->sub[i]);
            octree_flush_vec_rtx_triangle(root);
            return;
        }
    printf("Error: incohent octree.\n");
    exit(84);
}
