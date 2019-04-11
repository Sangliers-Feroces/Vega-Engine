/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

void world_init(demo_t *demo)
{
    demo->world.chunk_count = 0;
    demo->world.chunk_allocated = 0;
    demo->world.chunk = NULL;
    demo->world.chunk2d_area = (srect){{0, 0}, {1, 1}};
    demo->world.chunk2d = (chunk_t**)malloc_safe(sizeof(chunk_t*));
    demo->world.chunk2d[0] = NULL;
}

void world_quit(demo_t *demo)
{
    for (size_t i = 0; i < demo->world.chunk_count; i++)
        chunk_destroy(demo->world.chunk[i]);
    free(demo->world.chunk);
    free(demo->world.chunk2d);
}
