/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** nvidia fanboyisme
*/

#include "headers.h"

#include "global_shenanigans_vol.h"

void lightmap_init(void)
{
    _lightmaps = texture_cluster_create();
}

void lightmap_quit(void)
{
    texture2f_write(_lightmaps.base);
    texture_cluster_destroy(_lightmaps);
}

int lightmap_allocate(ivec2 size, texture_cluster_row_alloc **pres)
{
    return texture_cluster_allocate(&_lightmaps, size, pres);
}
