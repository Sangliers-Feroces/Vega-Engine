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

vec_chunk_dvertex_t vec_chunk_dvertex_create(size_t count)
{
    vec_chunk_dvertex_t res;

    res.count = count;
    res.dvertex =
    (chunk_dvertex_t*)malloc_safe(count * sizeof(chunk_dvertex_t));
    return res;
}

void vec_chunk_dvertex_destroy(vec_chunk_dvertex_t vec)
{
    free(vec.dvertex);
}

static void fill_buf(vec_rtx_triangle *geom, vec_chunk_vertex_t *buf)
{
    size_t ndx = 0;

    for (size_t i = 0; i < geom->count; i++)
        for (size_t j = 0; j < 3; j++)
            buf->vertex[ndx++] = (chunk_vertex_t){
            dvec3_vec3(geom->triangle[i]->vertex[j]),
            dvec3_vec3(geom->triangle[i]->normal),
            geom->triangle[i]->albelo.uv[j],
            geom->triangle[i]->lightmap.uv[j]};
}

void chunk_lod_reupload_buf(chunk_lod_t *lod)
{
    vec_chunk_vertex_t buf =
    vec_chunk_vertex_create(lod->geom->count * 3);

    fill_buf(lod->geom, &buf);
    glBindBuffer(GL_ARRAY_BUFFER, lod->vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER,
    buf.count * sizeof(chunk_vertex_t), buf.vertex, GL_STATIC_DRAW);
    lod->vertex_count = buf.count;
    vec_chunk_vertex_destroy(buf);
    lod->do_reupload_buf = 0;
}
