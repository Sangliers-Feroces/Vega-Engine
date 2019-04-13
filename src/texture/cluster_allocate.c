/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** nvidia fanboyisme
*/

#include "headers.h"

/* the texture is subdivided into rows of height 2^n */

static int try_lookup_row(texture_cluster_row *row, ivec2 size,
int32_t *pres, int32_t *start)
{
    int32_t cur_end;
    size_t i = row->to_lookup;

    if (i + 1 >= row->row_allocs.count) {
        row->to_lookup = 0;
        return 0;
    }
    cur_end = row->row_allocs.cluster_row[i]->start +
    row->row_allocs.cluster_row[i]->size;
    if (row->row_allocs.cluster_row[i + 1]->start - cur_end >=
    size.x + TEXTURE_ALLOC_MARGIN) {
        *pres = i + 1;
        *start = cur_end;
        row->to_lookup = *pres;
        return 1;
    }
    return 0;
}

int texture_cluster_alloc_try_fast_lookup(texture_cluster *cluster,
ivec2 size, int32_t power, texture_cluster_row_alloc **pres)
{
    int32_t pos;
    int32_t start;

    for (size_t i = 0; i < cluster->rows.count; i++) {
        if (cluster->rows.cluster_row[i].power != power)
            continue;
        if (try_lookup_row(&cluster->rows.cluster_row[i], size,
        &pos, &start)) {
            *pres = texture_cluster_insert_alloc(cluster,
            (texture_cluster_alloc_info){i, power, size}, pos, start);
            return 1;
        }
    }
    return 0;
}

texture_cluster_row_alloc* texture_cluster_insert_alloc(
texture_cluster *cluster, texture_cluster_alloc_info info,
int32_t pos, int32_t start)
{
    texture_cluster_row_alloc *res;

    res = vec_texture_cluster_row_alloc_insert(
    &cluster->rows.cluster_row[info.row].row_allocs, pos,
    start, info.size.x + TEXTURE_ALLOC_MARGIN);
    res->row = info.row;
    res->rect.p = (vec2){(float)start / (float)cluster->base->w,
    (float)cluster->rows.cluster_row[info.row].h / (float)cluster->base->h};
    res->rect.s = (vec2){(float)info.size.x / (float)cluster->base->w,
    (float)info.size.y / (float)cluster->base->h};
    return res;
}

static int try_allocate_on_row(texture_cluster *cluster,
texture_cluster_alloc_info info, texture_cluster_row_alloc **pres)
{
    int32_t pos;
    int32_t start;

    if (cluster->rows.cluster_row[info.row].power != info.power)
        return 0;
    if (!texture_cluster_row_search(&cluster->rows.cluster_row[info.row],
    info.size, &pos, &start))
        return 0;
    *pres = texture_cluster_insert_alloc(cluster, info, pos, start);
    return 1;
}

static int32_t get_power(int32_t x)
{
    int32_t res = 0;

    for (size_t i = 0; i < 32; i++)
        if (x & (1 << i))
            res = i;
    if ((1 << res) < x)
        res++;
    return res;
}

int texture_cluster_allocate(texture_cluster *cluster, ivec2 size,
texture_cluster_row_alloc **pres)
{
    int32_t power = get_power(size.y);

    if (power > 12)
        return 0;
    if (texture_cluster_alloc_try_fast_lookup(cluster, size, power, pres))
        return 1;
    for (size_t i = 0; i < cluster->rows.count; i++)
        if (try_allocate_on_row(cluster,
        (texture_cluster_alloc_info){i, power, size}, pres))
            return 1;
    if (!texture_cluster_add_row(cluster, power))
        return 0;
    return try_allocate_on_row(cluster,
    (texture_cluster_alloc_info){cluster->rows.count - 1, power, size}, pres);
}

static void free_vec_texture_cluster_row(vec_texture_cluster_row *vec)
{
    for (size_t i = 0; i < vec->count; i++) {
        for (size_t j = 0; j < vec->cluster_row[i].row_allocs.count; j++)
            free(vec->cluster_row[i].row_allocs.cluster_row[j]);
        free(vec->cluster_row[i].row_allocs.cluster_row);
    }
    free(vec->cluster_row);
}

void texture_cluster_destroy(texture_cluster cluster)
{
    texture2f_destroy(cluster.base);
    free_vec_texture_cluster_row(&cluster.rows);
}
