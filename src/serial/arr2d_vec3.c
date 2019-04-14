/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** nvidia fanboyisme
*/

#include "headers.h"

arr2d_vec3_t arr2d_vec3_create(size_t w, size_t h)
{
    arr2d_vec3_t res;

    res.w = w;
    res.h = h;
    res.vec3 = (vec3*)malloc_safe(res.w * res.h * sizeof(vec3));
    return res;
}

void arr2d_vec3_destroy(arr2d_vec3_t arr)
{
    free(arr.vec3);
}

arr_vec3_t arr_vec3_create(size_t count)
{
    arr_vec3_t res;

    res.count = count;
    res.vec3 = (vec3*)malloc_safe(res.count * sizeof(vec3));
    return res;
}

void arr_vec3_destroy(arr_vec3_t arr)
{
    free(arr.vec3);
}

void chunk_border_destroy(chunk_border_t border)
{
    for (size_t i = 0; i < CHUNK_GEN_ITER; i++)
        for (size_t j = 0; j < 2; j++) {
            arr_vec3_destroy(border.hor[i][j]);
            arr_vec3_destroy(border.ver[i][j]);
        }
}
