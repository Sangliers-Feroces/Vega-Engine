/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** optiiiiiii rtx
*/

#include "headers.h"

static int do_continue(thread_bus *bus, size_t i, size_t max)
{
    if (count % 1024)
        return (1);
    bus->progress = (float)i / (float)(max - 1);
    return (bus->task != THREAD_TASK_ABORT);
}

void octree_light_rtx_thread(thread_bus *bus, octree *tree, size_t density)
{
    vec2 pos;
    vec2 size;
    vec3 ray = {1.0f, -1.0f, 1.0f};
    size_t count;

    octree_ray_bound(tree, ray, &pos, &size);
    count = (double)(density * density) * (double)size.x * (double)size.y;
    for (size_t i = 0; i < count; i++) {
        throw_ray(tree, (ray3_color){
        {{pos.x + randf() * size.x, tree->bounds.max.y,
        pos.y + randf() * size.y}, ray}, {1.0f, 1.0f, 1.0f}, 16});
        if (!do_continue(bus, i, max))
            break;
    }
}

void octree_light_rtx_noblock(octree *tree, size_t density)
{
    octree_reset_lumels(tree);
    thread_send_each(THREAD_TASK_RAY_TRACING,
    (uint64_t[]){(uint64_t)tree, density / _thread.count}, 2);
}
