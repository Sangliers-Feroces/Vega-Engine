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

rtx_triangle* rtx_triangle_create(vec3 *triangle)
{
    rtx_triangle *res = (rtx_triangle*)malloc_safe(sizeof(rtx_triangle));

    for (size_t i = 0; i < 3; i++)
        res->vertex[i] = triangle[i];
    res->lightmap = texture2f_binding_create(triangle);
    res->albelo = texture2_binding_create(triangle);
    rtx_triangle_update_tangent(res);
    return (res);
}

void rtx_triangle_destroy(rtx_triangle *triangle)
{
    texture2f_binding_free(triangle->lightmap);
    free(triangle);
}
