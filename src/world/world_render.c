/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

void chunk_load_reupload_buf(chunk_lod_t *lod)
{
    lod->do_reupload_buf = 0;
}

static void chunk_lod_render(chunk_lod_t *lod)
{
    if (lod->do_reupload_buf)
        chunk_load_reupload_buf(lod);
}

static void chunk_render(chunk_t *chunk)
{
    chunk_lod_render(&chunk->lod[0]);
}

void world_render(demo_t *demo)
{
    for (size_t i = 0; i < demo->world.chunk_count; i++)
        chunk_render(demo->world.chunk[i]);
}
