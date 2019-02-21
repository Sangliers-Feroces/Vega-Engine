/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** nvidia fanboyisme
*/

#include "headers.h"

/* a constructor, an std::vector method */

vec3 normal3(vec3 a, vec3 b, vec3 c)
{
    return vec3_normalize(vec3_cross(vec3_sub(b, a), vec3_sub(c, a)));
}

rtx_triangle rtx_triangle_create(vec3 *triangle)
{
    rtx_triangle res = {{triangle[0], triangle[1], triangle[2]}, {NULL,
    {{0.0f, 0.0f}, {0.0f, 0.0f}}, 0}, NULL,
    {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}};

    if (res.lightmap.texture == NULL) {
        res.lightmap = texture2_binding_create(triangle);
        res.lumels = texture2f_create(
        res.lightmap.texture->w, res.lightmap.texture->h);
    }
    res.normal = normal3(triangle[0], triangle[1], triangle[2]);
    res.tangent = vec3_sub(triangle[1], triangle[0]);
    res.bitangent = normal3((vec3){0.0f, 0.0f, 0.0f}, res.tangent, res.normal);
    return (res);
}

void rtx_triangle_destroy(rtx_triangle triangle)
{
    texture2_binding_destroy(triangle.lightmap);
    texture2f_destroy(triangle.lumels);
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

void vec_rtx_triangle_destroy(vec_rtx_triangle vec)
{
    for (size_t i = 0; i < vec.count; i++)
        rtx_triangle_destroy(vec.triangle[i]);
    free(vec.triangle);
}
