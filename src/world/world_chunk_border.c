/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static void fetch_hor(chunk_border_t *res, ssize2 pos)
{
    dvec3 v = dvec3_init(CHUNK_SIZE, 0.0, 0.0);
    chunk_t **adj;

    chunk_try_load(ssize2_add(pos, (ssize2){-1, 0}), NULL);
    adj = world_chunk2d_get(_demo, ssize2_add(pos, (ssize2){-1, 0}));
    if ((adj != NULL) && (*adj != NULL))
        for (size_t i = 0; i < CHUNK_GEN_ITER; i++) {
            res->hor[i][0] = arr_dvec3_create((*adj)->border.hor[i][1].count);
            for (size_t j = 0; j < res->hor[i][0].count; j++)
                res->hor[i][0].dvec3[j] =
                dvec3_sub((*adj)->border.hor[i][1].dvec3[j], v);
        }
    chunk_try_load(ssize2_add(pos, (ssize2){1, 0}), NULL);
    adj = world_chunk2d_get(_demo, ssize2_add(pos, (ssize2){1, 0}));
    if ((adj != NULL) && (*adj != NULL))
        for (size_t i = 0; i < CHUNK_GEN_ITER; i++) {
            res->hor[i][1] = arr_dvec3_create((*adj)->border.hor[i][0].count);
            for (size_t j = 0; j < res->hor[i][1].count; j++)
                res->hor[i][1].dvec3[j] =
                dvec3_add((*adj)->border.hor[i][0].dvec3[j], v);
        }
}

static void fetch_ver(chunk_border_t *res, ssize2 pos)
{
    dvec3 v = dvec3_init(0.0, 0.0, CHUNK_SIZE);
    chunk_t **adj;

    chunk_try_load(ssize2_add(pos, (ssize2){0, -1}), NULL);
    adj = world_chunk2d_get(_demo, ssize2_add(pos, (ssize2){0, -1}));
    if ((adj != NULL) && (*adj != NULL))
        for (size_t i = 0; i < CHUNK_GEN_ITER; i++) {
            res->ver[i][0] = arr_dvec3_create((*adj)->border.ver[i][1].count);
            for (size_t j = 0; j < res->ver[i][0].count; j++)
                res->ver[i][0].dvec3[j] =
                dvec3_sub((*adj)->border.ver[i][1].dvec3[j], v);
        }
    chunk_try_load(ssize2_add(pos, (ssize2){0, 1}), NULL);
    adj = world_chunk2d_get(_demo, ssize2_add(pos, (ssize2){0, 1}));
    if ((adj != NULL) && (*adj != NULL))
        for (size_t i = 0; i < CHUNK_GEN_ITER; i++) {
            res->ver[i][1] = arr_dvec3_create((*adj)->border.ver[i][0].count);
            for (size_t j = 0; j < res->ver[i][1].count; j++)
                res->ver[i][1].dvec3[j] =
                dvec3_add((*adj)->border.ver[i][0].dvec3[j], v);
        }
}

chunk_border_t chunk_border_fetch(ssize2 pos)
{
    chunk_border_t res;

    for (size_t i = 0; i < CHUNK_GEN_ITER; i++)
        for (size_t j = 0; j < 2; j++) {
            res.hor[i][j] = (arr_dvec3_t){0, NULL};
            res.ver[i][j] = (arr_dvec3_t){0, NULL};
        }
    //fetch_hor(&res, pos);
    //fetch_ver(&res, pos);
    return res;
}

chunk_border_t chunk_border_init(void)
{
    chunk_border_t res;

    for (size_t i = 0; i < CHUNK_GEN_ITER; i++)
        for (size_t j = 0; j < 2; j++) {
            res.hor[i][j] = (arr_dvec3_t){0, NULL};
            res.ver[i][j] = (arr_dvec3_t){0, NULL};
        }
    return res;
}
