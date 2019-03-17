/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#ifndef _TERRAIN_H
#define _TERRAIN_H

rtx_triangle* octree_add_triangle(octree **tree, vec3 *triangle);
rtx_triangle* octree_add_triangle_no_lightmap(octree **tree, vec3 *triangle);
void terrain_gen(demo_t *demo, float size, size_t iter, float strengh);


void terrain_sub_triangle(rtx_triangle *triangle, octree **dst);
void terrain_sub_triangle2(rtx_triangle *triangle, octree *root, octree **dst,
float strengh);

void terrain_apply_texture(octree *tree, texture2 *texture);

#endif
