/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

rtx_triangle* octree_add_triangle(octree **tree, dvec3 *triangle)
{
    rtx_triangle *rtx = rtx_triangle_create(triangle);

    octree_insert_triangle(tree, rtx);
    return rtx;
}

rtx_triangle* octree_add_triangle_no_lightmap(octree **tree, dvec3 *triangle)
{
    rtx_triangle *rtx = rtx_triangle_create_no_lightmap(triangle);

    octree_insert_triangle(tree, rtx);
    return rtx;
}

void terrain_sub_triangle(rtx_triangle *triangle, octree **dst)
{
    dvec3 mid = {0.0f, 0.0f, 0.0f};
    float dist = dvec3_dist(triangle->vertex[0], triangle->vertex[1]);

    for (size_t i = 0; i < 3; i++)
        mid = dvec3_add(mid, triangle->vertex[i]);
    mid = dvec3_divs(mid, 3.0f);
    mid = dvec3_add(mid, dvec3_muls(triangle->normal,
    (randf() - 0.5f) * dist * 0.2f));
    octree_add_triangle_no_lightmap(dst,
    (dvec3[]){triangle->vertex[0], triangle->vertex[1], mid});
    octree_add_triangle_no_lightmap(dst,
    (dvec3[]){triangle->vertex[1], triangle->vertex[2], mid});
    octree_add_triangle_no_lightmap(dst,
    (dvec3[]){triangle->vertex[2], triangle->vertex[0], mid});
}

void terrain_gen(demo_t *demo, float size, size_t iter, float strengh)
{
    (void)demo;
    (void)size;
    (void)iter;
    (void)strengh;
}
