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
        chunk_insert_rtx_triangle(
        world_chunk_get_by_pos(demo, vec.triangle[i]->vertex[0]), vec.triangle[i]);
}
