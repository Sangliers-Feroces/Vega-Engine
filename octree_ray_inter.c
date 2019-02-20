/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** optiiiiiii rtx
*/

#include "headers.h"

/* intersection of a ray and a bunch of triangle using the octree */

static void intersect_ray(rtx_triangle *triangle, ray3 ray, inter_ray3 *inter)
{
    float dotnd = vec3_dot(triangle->normal, ray.v);
    float t;
    vec3 p;

    if (dotnd == 0.0f)
        return;
    t = vec3_dot(triangle->normal, vec3_sub(triangle->vertex[0], ray.p)) /
    dotnd;
    if (t < 0.0f)
        return;
    p = ray3_compute(ray, t);
    if (!is_point_in_triangle(p, triangle->vertex))
        return;
    printf("hit, t: %f\n", t);
    if ((inter->triangle == NULL) || (t < inter->min_t)) {
        inter->triangle = triangle;
        inter->p = p;
        inter->min_t = t;
    }
}

static void tree_intersect_ray(octree *tree, ray3 ray, inter_ray3 *inter)
{
    if (tree == NULL)
        return;
    if (!is_ray_in_bounds(ray, tree->bounds))
        return;
    for (size_t i = 0; i < 8; i++)
        tree_intersect_ray(tree->sub[i], ray, inter);
    for (size_t i = 0; i < tree->triangles.count; i++)
        intersect_ray(&tree->triangles.triangle[i], ray, inter);
}

inter_ray3 octree_intersect_ray(octree *tree, ray3 ray)
{
    inter_ray3 inter = {NULL, {0.0f, 0.0f, 0.0f}, 0.0f};

    tree_intersect_ray(tree, ray, &inter);
    return inter;
}
