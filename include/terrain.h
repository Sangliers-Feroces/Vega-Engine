/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#pragma once

void terrain_gen(demo_t *demo, float size, size_t iter, float strengh);

void terrain_sub_triangle(rtx_triangle *triangle, octree **dst);
void terrain_sub_triangle2(rtx_triangle *triangle, octree *root, octree **dst,
float strengh);

void terrain_apply_texture(octree *tree, texture2 *texture);
