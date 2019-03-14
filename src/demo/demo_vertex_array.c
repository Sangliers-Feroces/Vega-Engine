/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** demo_vertex_array
*/

#include "headers.h"

static size_t octree_get_count(vec_rtx_triangle *vec)
{
    return vec->count;
}

static size_t octree_get_triangle_nbr(octree *tree, size_t size)
{
    if (tree == NULL)
        return size;
    size += octree_get_count(&tree->triangles);
    for (int i = 0; i < 8; i++)
        size = octree_get_triangle_nbr(tree->sub[i], size);
    return size;
}

static void fill_array(vertex_struct_t *v_struct, vec_rtx_triangle vec)
{
    for (size_t i = 0; i < vec.count; i++)
        for (int j = 0; j < 3; j++) {
            v_struct->v_array[v_struct->offset].point =
            vec.triangle[i]->vertex[j];
            v_struct->v_array[v_struct->offset].uv =
            vec.triangle[i]->lightmap.uv[j];
            v_struct->offset++;
        }
}

static void octree_fill_vertex_array(octree *tree,
vertex_struct_t *vertex_struct)
{
    if (tree == NULL)
        return;
    if (tree->triangles.count > 0)
            fill_array(vertex_struct, tree->triangles);
    for (int i = 0; i < 8; i++)
        octree_fill_vertex_array(tree->sub[i], vertex_struct);
}

void refresh_vertex_buffer(demo_t *demo)
{
    vertex_struct_t vertex_struct;

    vertex_struct.offset = 0;
    vertex_struct.count = octree_get_triangle_nbr(demo->tree, 0);
    vertex_struct.v_array = malloc_safe(
    sizeof(vertext_array_t) * (vertex_struct.count * 3));
    octree_fill_vertex_array(demo->tree, &vertex_struct);
    free(demo->buf.vertex_struct.v_array);
    demo->buf.vertex_struct = vertex_struct;
}
