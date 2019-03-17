/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#ifndef _TERRAIN_H
#define _TERRAIN_H

void octree_add_triangle(octree **tree, vec3 *triangle);
void terrain_gen(demo_t *demo, float size, size_t iter);

#endif
