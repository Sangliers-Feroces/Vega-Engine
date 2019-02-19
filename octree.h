/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** sanic
*/

#ifndef _OCTREE_H
#define _OCTREE_H

#include "octree_mem.h"

rtx_triangle rtx_triangle_create(vec3 *triangle);
void vec_rtx_triangle_add(vec_rtx_triangle *vec, rtx_triangle *to_add);

void octree_insert_triangle(octree **tree, rtx_triangle *triangle);

void octree_enlarge(octree **tree, rtx_triangle *triangle);

octree* octree_create(octree *root);
octree* octree_create_node(octree *root, bounds3 bounds);
void octree_destroy(octree **root);

bounds3 octree_get_sub_bounds(octree *tree, size_t ndx);

size_t get_triangle_upper_tree(vec3 *triangle, bounds3 bounds);

#endif
