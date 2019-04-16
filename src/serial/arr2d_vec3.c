/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** nvidia fanboyisme
*/

#include "headers.h"

arr2d_dvec3_t arr2d_dvec3_create(size_t w, size_t h)
{
    arr2d_dvec3_t res;

    res.w = w;
    res.h = h;
    res.dvec3 = (dvec3*)malloc_safe(res.w * res.h * sizeof(dvec3));
    return res;
}

void arr2d_dvec3_destroy(arr2d_dvec3_t arr)
{
    free(arr.dvec3);
}

arr_dvec3_t arr_dvec3_create(size_t count)
{
    arr_dvec3_t res;

    res.count = count;
    res.dvec3 = (dvec3*)malloc_safe(res.count * sizeof(dvec3));
    return res;
}

void arr_dvec3_destroy(arr_dvec3_t arr)
{
    free(arr.dvec3);
}

void chunk_border_destroy(chunk_border_t border)
{
    for (size_t i = 0; i < CHUNK_GEN_ITER; i++)
        for (size_t j = 0; j < 2; j++) {
            arr_dvec3_destroy(border.hor[i][j]);
            arr_dvec3_destroy(border.ver[i][j]);
        }
}
