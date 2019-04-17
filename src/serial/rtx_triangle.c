/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** nvidia fanboyisme
*/

#include "headers.h"

/* a constructor, an std::vector method */

dvec3 normal3(dvec3 a, dvec3 b, dvec3 c)
{
    return dvec3_normalize(dvec3_cross(dvec3_sub(b, a), dvec3_sub(c, a)));
}

rtx_triangle* rtx_triangle_create(dvec3 *triangle)
{
    rtx_triangle *res = (rtx_triangle*)malloc_safe(sizeof(rtx_triangle));

    for (size_t i = 0; i < 3; i++)
        res->vertex[i] = triangle[i];
    res->lightmap = texture2f_binding_create(triangle);
    res->albelo = texture2_binding_create(triangle);
    res->material = MATERIAL_GRASS;
    res->ref = vec_rtx_triangle_ref_null();
    rtx_triangle_update_tangent(res);
    return (res);
}

rtx_triangle* rtx_triangle_create_param(dvec3 *triangle, int alloc_lightmap)
{
    rtx_triangle *res = (rtx_triangle*)malloc_safe(sizeof(rtx_triangle));

    for (size_t i = 0; i < 3; i++)
        res->vertex[i] = triangle[i];
    if (alloc_lightmap)
        res->lightmap = texture2f_binding_create(triangle);
    else {
        res->lightmap.alloc = NULL;
        res->lightmap.texture = NULL;
    }
    res->albelo = texture2_binding_create(triangle);
    res->material = MATERIAL_GRASS;
    res->ref = vec_rtx_triangle_ref_null();
    rtx_triangle_update_tangent(res);
    return (res);
}


rtx_triangle* rtx_triangle_create_discrete(dvec3 a, dvec3 b, dvec3 c)
{
    dvec3 data[3] = {a, b, c};

    return rtx_triangle_create_param(data, 0);
}

void rtx_triangle_destroy(rtx_triangle *triangle)
{
    vec_rtx_triangle *ref_vec;

    if (triangle->ref.vec != NULL) {
        ref_vec = triangle->ref.vec;
        ref_vec->triangle[triangle->ref.ndx] =
        ref_vec->triangle[--ref_vec->count];
        if ((ref_vec->count > 0) &&
        (ref_vec->triangle[triangle->ref.ndx]->ref.vec == ref_vec))
            ref_vec->triangle[triangle->ref.ndx]->ref.ndx = triangle->ref.ndx;
    }
    texture2f_binding_free(triangle->lightmap);
    free(triangle);
}
