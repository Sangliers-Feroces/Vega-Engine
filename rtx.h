/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** std::vector
*/

#ifndef _RTX_H
#define _RTX_H

void vec_rtx_triangle_add(vec_rtx_triangle *vec, rtx_triangle *to_add);

void octree_insert_triangle(octree **tree, rtx_triangle *triangle);

octree* octree_create(octree *root);
octree* octree_create_node(octree *root, bounds3 bounds);

bounds3 octree_get_sub_bounds(octree *tree, size_t ndx);

size_t get_triangle_upper_tree(vec3 *triangle, bounds3 bounds);

rtx_triangle rtx_triangle_create(vec3 *triangle);

#endif
