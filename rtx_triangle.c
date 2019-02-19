/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** nvidia fanboyisme
*/

#include "headers.h"

/* a constructor, an std::vector method */

rtx_triangle rtx_triangle_create(vec3 *triangle)
{
    rtx_triangle res = {{triangle[0], triangle[1], triangle[2]},
    {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}};

    return (res);
}

void vec_rtx_triangle_add(vec_rtx_triangle *vec, rtx_triangle *to_add)
{
    size_t cur = vec->count++;
    rtx_triangle *new_triangle;

    if (vec->count > vec->allocated) {
        vec->allocated += OCTREE_ALLOC_STEP;
        new_triangle = (rtx_triangle*)malloc_safe(vec->allocated *
        sizeof(rtx_triangle));
        for (size_t i = 0; i < (vec->allocated - OCTREE_ALLOC_STEP); i++)
            new_triangle[i] = vec->triangle[i];
        free(vec->triangle);
        vec->triangle = new_triangle;
    }
    vec->triangle[cur] = *to_add;
}
