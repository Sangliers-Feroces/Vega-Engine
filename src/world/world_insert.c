/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

void world_insert_vec_rtx_triangle(demo_t *demo, vec_rtx_triangle vec)
{
    for (size_t i = 0; i < vec.count; i++)
        octree_insert_triangle(&demo->tree, vec.triangle[i]);
}
