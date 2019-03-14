/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** optiiiiiii rtx
*/

#include "headers.h"

static int intersect_ray(vec3 plane, ray3 ray, vec3 *pres)
{
    vec3 normal = {0.0f, 1.0f, 0.0f};
    float dotnv = vec3_dot(normal, ray.v);
    float t;

    if (dotnv >= 0.0f)
        return 0;
    t = vec3_dot(normal, vec3_sub(plane, ray.p)) / dotnv;
    *pres = ray3_compute(ray, t);
    return 1;
}

void octree_ray_bound(octree *tree, vec3 ray, vec2 *ppos, vec2 *psize)
{
    vec3 p;
    vec3 size;

    if (!intersect_ray(tree->bounds.max, (ray3){tree->bounds.min, ray}, &p)) {
        *ppos = (vec2){0.0f, 0.0f};
        *psize = *ppos;
        return;
    }
    *ppos = (vec2){p.x, p.z};
    size = vec3_sub(tree->bounds.max, p);
    *psize = (vec2){size.x, size.z};
}
