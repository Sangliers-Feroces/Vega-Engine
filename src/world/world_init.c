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
    demo->buf.l = dvec3_normalize(dvec3_add(dvec3_init(-1.0, -1.0, -1.0), dvec3_init(0.0, 0.0, 0.2)));
}

void world_quit(demo_t *demo)
{
    while (demo->world.chunk_count > 0)
        chunk_destroy(demo->world.chunk[0]);
    free(demo->world.chunk);
    free(demo->world.chunk2d);
}
