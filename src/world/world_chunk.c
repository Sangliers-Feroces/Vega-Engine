/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

chunk_t* chunk_create(ssize2 pos)
{
    chunk_t *res = (chunk_t*)malloc_safe(sizeof(chunk_t));

    res->pos = pos;
    res->tree = octree_create(NULL);
    return res;
}

void chunk_destroy(chunk_t *chunk)
{
    octree_destroy(&chunk->tree);
    free(chunk);
}

chunk_t* world_get_chunk2d(demo_t *demo, ssize2 pos)
{
    ssize2 ndx = ssize2_sub(demo->world.chunk2d_area.p, pos);

    return demo->world.chunk2d[ndx.y * demo->world.chunk2d_area.s.x + ndx.x];
}

chunk_t* world_get_chunk(demo_t *demo, ssize2 pos)
{
    //return world_get_chunk2d()
}

void chunk_insert_rtx_triangle(chunk_t *chunk, rtx_triangle *triangle)
{
    octree_insert_triangle(&chunk->tree, triangle);
}
