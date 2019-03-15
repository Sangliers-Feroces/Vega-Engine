/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** optiiiiiii rtx
*/

#include "headers.h"

/* intersection of a ray and a bunch of triangle using the octree */
// si ça dépasse un peu, ça passe

static float intersect_plane(rtx_triangle *triangle, ray3 ray, float dotnv)
{
    return vec3_dot(triangle->normal, vec3_sub(triangle->vertex[0], ray.p)) /
    dotnv;
}

static void intersect_ray(rtx_triangle *triangle, ray3 ray, inter_ray3 *inter)
{
    float dotnv = vec3_dot(triangle->normal, ray.v);
    float t;
    vec3 p;
    vec3 bar;

    if (dotnv >= 0.0f)
        return;
    t = intersect_plane(triangle, ray, dotnv);
    if (t <= 0.0f)
        return;
    p = ray3_compute(ray, t);
    bar = barycentric3(p, triangle->vertex);
    if (!is_barycentric_valid_laxist(bar))
        return;
    if ((inter->triangle == NULL) || (t < inter->min_t)) {
        inter->triangle = triangle;
        inter->p = p;
        inter->bar = bar;
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
        intersect_ray(tree->triangles.triangle[i], ray, inter);
}

inter_ray3 octree_intersect_ray_laxist(octree *tree, ray3 ray)
{
    inter_ray3 inter = {NULL, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, 0.0f};

    tree_intersect_ray(tree, ray, &inter);
    return inter;
}