/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

vec_chunk_vertex_t vec_chunk_vertex_create(size_t count)
{
    vec_chunk_vertex_t res;

    res.count = count;
    res.vertex =
    (chunk_vertex_t*)malloc_safe(count * sizeof(chunk_vertex_t));
    return res;
}

void vec_chunk_vertex_destroy(vec_chunk_vertex_t vec)
{
    free(vec.vertex);
}

static void fill_buf_actual(octree *tree, vec_chunk_vertex_t *buf, size_t *ndx)
{
    if (tree == NULL)
        return;
    for (size_t i = 0; i < 8; i++)
        fill_buf_actual(tree->sub[i], buf, ndx);
    for (size_t i = 0; i < tree->triangles.count; i++)
        for (size_t j = 0; j < 3; j++)
            buf->vertex[(*ndx)++] =
            (chunk_vertex_t){tree->triangles.triangle[i]->vertex[j],
            tree->triangles.triangle[i]->normal,
            tree->triangles.triangle[i]->albelo.uv[j],
            tree->triangles.triangle[i]->lightmap.uv[j]};
}

static void fill_buf(octree *tree, vec_chunk_vertex_t *buf)
{
    size_t ndx = 0;

    fill_buf_actual(tree, buf, &ndx);
}

void chunk_lod_reupload_buf(chunk_lod_t *lod)
{
    vec_chunk_vertex_t buf =
    vec_chunk_vertex_create(octree_get_rtx_triangle_count(lod->tree) * 3);

    fill_buf(lod->tree, &buf);
    glBindBuffer(GL_ARRAY_BUFFER, lod->vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER,
    buf.count * sizeof(chunk_vertex_t), buf.vertex, GL_STATIC_DRAW);
    lod->vertex_count = buf.count;
    vec_chunk_vertex_destroy(buf);
    lod->do_reupload_buf = 0;
}
