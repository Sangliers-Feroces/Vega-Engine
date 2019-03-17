/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

void octree_add_triangle(octree **tree, vec3 *triangle)
{
    rtx_triangle *rtx = rtx_triangle_create(triangle);

    octree_insert_triangle(tree, rtx);
}

static void sub_triangle(rtx_triangle *triangle, octree **dst)
{
    vec3 mid = {0.0f, 0.0f, 0.0f};
    float dist = vec3_dist(triangle->vertex[0], triangle->vertex[1]);

    for (size_t i = 0; i < 3; i++)
        mid = vec3_add(mid, triangle->vertex[i]);
    mid = vec3_divs(mid, 3.0f);
    mid = vec3_add(mid, vec3_muls(triangle->normal,
    (randf() - 0.5f) * dist * 0.2f));
    octree_add_triangle(dst,
    (vec3[]){triangle->vertex[0], triangle->vertex[1], mid});
    octree_add_triangle(dst,
    (vec3[]){triangle->vertex[1], triangle->vertex[2], mid});
    octree_add_triangle(dst,
    (vec3[]){triangle->vertex[2], triangle->vertex[0], mid});
}

static void sub_triangle2(rtx_triangle *triangle, octree **dst)
{
    vec3 mid;
    float dist;

    mid = vec3_add(triangle->vertex[1], triangle->vertex[2]);
    mid = vec3_divs(mid, 2.0f);
    dist = vec3_dist(triangle->vertex[1], triangle->vertex[2]);
    mid = vec3_add(mid, vec3_muls(triangle->normal,
    (randf() - 0.5f) * dist * 0.3f));
    octree_add_triangle(dst,
    (vec3[]){mid, triangle->vertex[0], triangle->vertex[1]});
    octree_add_triangle(dst,
    (vec3[]){mid, triangle->vertex[2], triangle->vertex[0]});
}

static void sub_terrain(demo_t *demo, octree *tree, octree **dst)
{
    if (tree == NULL)
        return;
    for (size_t i = 0; i < 8; i++)
        sub_terrain(demo, tree->sub[i], dst);
    for (size_t i = 0; i < tree->triangles.count; i++)
        sub_triangle(tree->triangles.triangle[i], dst);
}

void terrain_gen(demo_t *demo, float size, size_t iter)
{
    octree *new_tree;

    octree_add_triangle(&demo->tree,
    (vec3[]){{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, size}, {size, 0.0f, 0.0f}});
    octree_add_triangle(&demo->tree,
    (vec3[]){{size, 0.0f, 0.0f}, {0.0f, 0.0f, size}, {size, 0.0f, size}});
    for (size_t i = 0; i < iter; i++) {
        new_tree = octree_create(NULL);
        sub_terrain(demo, demo->tree, &new_tree);
        octree_destroy(&demo->tree);
        demo->tree = new_tree;
    }
}
