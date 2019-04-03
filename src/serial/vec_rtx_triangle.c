/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** nvidia fanboyisme
*/

#include "headers.h"

vec_rtx_triangle vec_rtx_triangle_create(void)
{
    return (vec_rtx_triangle){0, 0, NULL};
}

void vec_rtx_triangle_add(vec_rtx_triangle *vec, rtx_triangle *to_add)
{
    size_t cur = vec->count++;
    rtx_triangle **new_triangle;

    if (vec->count > vec->allocated) {
        vec->allocated += OCTREE_ALLOC_STEP;
        new_triangle = (rtx_triangle**)malloc_safe(vec->allocated *
        sizeof(rtx_triangle*));
        for (size_t i = 0; i < (vec->allocated - OCTREE_ALLOC_STEP); i++)
            new_triangle[i] = vec->triangle[i];
        free(vec->triangle);
        vec->triangle = new_triangle;
    }
    vec->triangle[cur] = to_add;
}

void vec_rtx_triangle_destroy(vec_rtx_triangle vec)
{
    for (size_t i = 0; i < vec.count; i++)
        rtx_triangle_destroy(vec.triangle[i]);
    free(vec.triangle);
}

void vec_rtx_triangle_free(vec_rtx_triangle vec)
{
    free(vec.triangle);
}
