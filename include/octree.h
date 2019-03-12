/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** sanic
*/

#ifndef _OCTREE_H
#define _OCTREE_H

#include "octree_mem.h"

void octree_insert_triangle(octree **tree, rtx_triangle *triangle);

void octree_enlarge(octree **tree, rtx_triangle *triangle);

octree* octree_create(octree *root);
octree* octree_create_node(octree *root, bounds3 bounds);
void octree_destroy(octree **root);

bounds3 octree_get_sub_bounds(octree *tree, size_t ndx);

size_t get_triangle_upper_tree(vec3 *triangle, bounds3 bounds);

inter_ray3 octree_intersect_ray(octree *tree, ray3 ray);

float octree_light_rtx(octree *tree, size_t rays);
void octree_light_rtx_thread(octree *tree, size_t rays);

void octree_reset_lumels(octree *tree);
float octree_get_max_lumel(octree *tree);
void octree_update_lightmap(octree *tree, float max_lumel);

vertex_struct_t get_vertex_array_from_octree(demo_t *demo);
#endif
