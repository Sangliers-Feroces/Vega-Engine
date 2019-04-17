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

void vec_rtx_triangle_add(vec_rtx_triangle *vec, rtx_triangle *to_add)
{
    size_t cur = vec->count++;
    rtx_triangle **new_triangle;

    if (vec->count > vec->allocated) {
        vec->allocated += OCTREE_ALLOC_STEP;
        new_triangle = (rtx_triangle**)malloc_safe(vec->allocated *
        sizeof(rtx_triangle*));
        for (size_t i = 0; i < cur; i++)
            new_triangle[i] = vec->triangle[i];
        free(vec->triangle);
        vec->triangle = new_triangle;
    }
    vec->triangle[cur] = to_add;
    to_add->ref.vec = vec;
    to_add->ref.ndx = cur;
}

void vec_rtx_triangle_add_detached(vec_rtx_triangle *vec, rtx_triangle *to_add)
{
    vec_rtx_triangle_ref base_ref = to_add->ref;

    vec_rtx_triangle_add(vec, to_add);
    to_add->ref = base_ref;
}

void vec_rtx_triangle_destroy(vec_rtx_triangle *vec)
{
    int is_linked;

    while (vec->count > 0) {
        is_linked = vec->triangle[vec->count - 1]->ref.vec == vec;
        rtx_triangle_destroy(vec->triangle[vec->count - 1]);
        if (!is_linked)
            vec->count--;
    }
    free(vec->triangle);
    free(vec);
}

void vec_rtx_triangle_free(vec_rtx_triangle *vec)
{
    for (size_t i = 0; i < vec->count; i++)
        if (vec->triangle[i]->ref.vec == vec)
            vec->triangle[i]->ref = vec_rtx_triangle_ref_null();
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

vec_rtx_triangle_ref vec_rtx_triangle_ref_null(void)
{
    return (vec_rtx_triangle_ref){NULL, ~0ULL};
}
