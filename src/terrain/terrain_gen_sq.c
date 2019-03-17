/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

void terrain_apply_texture(octree *tree, texture2 *texture)
{
    if (tree == NULL)
        return;
    for (size_t i = 0; i < 8; i++)
        terrain_apply_texture(tree->sub[i], texture);
    for (size_t i = 0; i < tree->triangles.count; i++) {
        tree->triangles.triangle[i]->albelo.texture = texture;
        rtx_triangle_update(tree->triangles.triangle[i]);
    }
}

static void sub_other(rtx_triangle *candidate, octree **dst,
terrain_search_t search)
{
    if (candidate->data)
        return;
    if (!(vec3_eq(candidate->vertex[1], search.vertex[2]) &&
    vec3_eq(candidate->vertex[2], search.vertex[1])))
        return;
    octree_add_triangle_no_lightmap(dst,
    (vec3[]){search.mid, candidate->vertex[0], candidate->vertex[1]});
    octree_add_triangle_no_lightmap(dst,
    (vec3[]){search.mid, candidate->vertex[2], candidate->vertex[0]});
    candidate->data = 1;
}

static void terrain_search_other(octree *tree, octree **dst,
terrain_search_t search)
{
    if (tree == NULL)
        return;
    for (size_t i = 0; i < 8; i++)
        terrain_search_other(tree->sub[i], dst, search);
    for (size_t i = 0; i < tree->triangles.count; i++)
        sub_other(tree->triangles.triangle[i], dst, search);
}

void terrain_sub_triangle2(rtx_triangle *triangle, octree *root, octree **dst,
float strengh)
{
    vec3 mid;
    float dist;

    if (triangle->data)
        return;
    mid = vec3_add(triangle->vertex[1], triangle->vertex[2]);
    mid = vec3_divs(mid, 2.0f);
    dist = vec3_dist(triangle->vertex[1], triangle->vertex[2]);
    mid = vec3_add(mid, vec3_muls(triangle->normal,
    (randf() - 0.5f) * dist * strengh));
    octree_add_triangle_no_lightmap(dst,
    (vec3[]){mid, triangle->vertex[0], triangle->vertex[1]});
    octree_add_triangle_no_lightmap(dst,
    (vec3[]){mid, triangle->vertex[2], triangle->vertex[0]});
    triangle->data = 1;
    terrain_search_other(root, dst,
    (terrain_search_t){triangle->vertex, mid});
}
