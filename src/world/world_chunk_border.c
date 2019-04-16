/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

chunk_border_t chunk_border_fetch(ssize2 pos)
{
    chunk_border_t res;
    chunk_t **adj;

    for (size_t i = 0; i < CHUNK_GEN_ITER; i++)
        for (size_t j = 0; j < 2; j++) {
            res.hor[i][j].dvec3 = NULL;
            res.ver[i][j].dvec3 = NULL;
        }
    adj = world_chunk2d_get(_demo, ssize2_add(pos, (ssize2){-1, 0}));
    if ((adj != NULL) && (*adj != NULL))
        for (size_t i = 0; i < CHUNK_GEN_ITER; i++)
            res.hor[i][0] = (*adj)->border.hor[i][1];
    adj = world_chunk2d_get(_demo, ssize2_add(pos, (ssize2){1, 0}));
    if ((adj != NULL) && (*adj != NULL))
        for (size_t i = 0; i < CHUNK_GEN_ITER; i++)
            res.hor[i][1] = (*adj)->border.hor[i][0];
    adj = world_chunk2d_get(_demo, ssize2_add(pos, (ssize2){0, -1}));
    if ((adj != NULL) && (*adj != NULL))
        for (size_t i = 0; i < CHUNK_GEN_ITER; i++)
            res.ver[i][0] = (*adj)->border.ver[i][1];
    adj = world_chunk2d_get(_demo, ssize2_add(pos, (ssize2){0, 1}));
    if ((adj != NULL) && (*adj != NULL))
        for (size_t i = 0; i < CHUNK_GEN_ITER; i++)
            res.ver[i][1] = (*adj)->border.ver[i][0];
    return res;
}
