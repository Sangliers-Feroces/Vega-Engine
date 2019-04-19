/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** nvidia fanboyisme
*/

#include "headers.h"

vec_rtx_triangle* vec_rtx_triangle_create(void)
{
    vec_rtx_triangle *res =
    (vec_rtx_triangle*)malloc_safe(sizeof(vec_rtx_triangle));

    *res = (vec_rtx_triangle){0, 0, NULL, NULL};
    return res;
}

static void vec_realloc(vec_rtx_triangle *vec)
{
    size_t cur = vec->allocated;
    rtx_triangle *new_triangle;

    vec->allocated += OCTREE_ALLOC_STEP;
    new_triangle = (rtx_triangle*)malloc_safe(vec->allocated *
    sizeof(rtx_triangle));
    for (size_t i = 0; i < cur; i++) {
        new_triangle[i] = vec->triangle[i];
        if (new_triangle[i].indirect != NULL)
            *new_triangle[i].indirect = &new_triangle[i];
    }
    free(vec->triangle);
    vec->triangle = new_triangle;
}

rtx_triangle* vec_rtx_triangle_add(vec_rtx_triangle *vec, rtx_triangle to_add)
{
    size_t cur = vec->count++;

    if (vec->count > vec->allocated)
        vec_realloc(vec);
    vec->triangle[cur] = to_add;
    vec->triangle[cur].root = vec;
    vec->triangle[cur].root_ndx = cur;
    return &vec->triangle[cur];
}

void vec_rtx_triangle_destroy(vec_rtx_triangle *vec)
{
    free(vec->triangle);
    free(vec);
}

void vec_rtx_triangle_free(vec_rtx_triangle *vec)
{
    free(vec->triangle);
    free(vec);
}

void vec_rtx_triangle_flush(vec_rtx_triangle *vec)
{
    if (vec->count > 0)
        return;
    free(vec->triangle);
    vec->triangle = NULL;
    vec->allocated = 0;
}
