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
}

void world_quit(demo_t *demo)
{
    for (size_t i = 0; i < demo->world.chunk_count; i++)
        chunk_destroy(demo->world.chunk[i]);
    free(demo->world.chunk);
}
