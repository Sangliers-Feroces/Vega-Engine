/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static entity3* try_load_global_ents(void)
{
    return NULL;
}

void world_init(demo_t *demo)
{
    demo->world.map_path = strdup("maps/world");
    demo->world.chunk_count = 0;
    demo->world.chunk_allocated = 0;
    demo->world.chunk = NULL;
    demo->world.triggers = vec_trigger_init();
    demo->world.ents = try_load_global_ents();
    demo->world.chunk2d_area = (srect){{0, 0}, {1, 1}};
    demo->world.chunk2d = (chunk_t**)malloc_safe(sizeof(chunk_t*));
    demo->world.chunk2d[0] = NULL;
    demo->world.tree = octree_create(NULL);
    demo->buf.l = dvec3_normalize(dvec3_add(dvec3_init(-1.0, -1.0, -1.0),
    dvec3_init(0.0, 0.0, 0.2)));
}

void world_quit(demo_t *demo)
{
    while (demo->world.chunk_count > 0)
        chunk_destroy(demo->world.chunk[0]);
    free(demo->world.chunk);
    free(demo->world.chunk2d);
    octree_destroy(&demo->world.tree);
    vec_trigger_destroy(demo->world.triggers);
    free(demo->world.map_path);
}
