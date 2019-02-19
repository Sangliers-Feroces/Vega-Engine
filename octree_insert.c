/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** optiiiiiii rtx
*/

#include "headers.h"

static int try_insert_sub(octree **tree, rtx_triangle *triangle)
{
    bounds3 sub_b;

    for (size_t i = 0; i < 8; i++) {
        sub_b = octree_get_sub_bounds(*tree, i);
        if (is_triangle_in_bounds(triangle->vertex, sub_b)) {
            (*tree)->sub[i] = octree_create_node(*tree, sub_b);
            octree_insert_triangle(&((*tree)->sub[i]), triangle);
            return 1;
        }
    }
    return 0;
}

static int try_insert_cur(octree **tree, rtx_triangle *triangle)
{
    if (is_triangle_in_bounds(triangle->vertex, (*tree)->bounds)) {
        vec_rtx_triangle_add(&((*tree)->triangles), triangle);
        return 1;
    } else
        return 0;
}

static void enlarge_get_bounds(octree *new_root, bounds3 old_b, size_t ndx)
{
    new_root->bounds.size = old_b.size * 2.0f;
    if (ndx == 0) {
        new_root->bounds.min = old_b.min;
        new_root->bounds.max =
        (vec3){new_root->bounds.min.x + new_root->bounds.size,
        new_root->bounds.min.y + new_root->bounds.size,
        new_root->bounds.min.z + new_root->bounds.size};
    } else {
        new_root->bounds.max = old_b.max;
        new_root->bounds.min =
        (vec3){new_root->bounds.max.x - new_root->bounds.size,
        new_root->bounds.max.y - new_root->bounds.size,
        new_root->bounds.max.z - new_root->bounds.size};
    }
}

static void octree_enlarge(octree **tree, rtx_triangle *triangle)
{
    octree *new_root = octree_create(NULL);
    size_t ndx;

    ndx = get_triangle_upper_tree(triangle->vertex, (*tree)->bounds);
    enlarge_get_bounds(new_root, (*tree)->bounds, ndx);
    (*tree)->root = new_root;
    new_root->sub[ndx] = *tree;
    *tree = new_root;
}

void octree_insert_triangle(octree **tree, rtx_triangle *triangle)
{
    while (1) {
        if (try_insert_sub(tree, triangle))
            return;
        else if (try_insert_cur(tree, triangle))
            return;
        octree_enlarge(tree, triangle);
    }
}
