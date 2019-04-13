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
