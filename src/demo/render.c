/*
** EPITECH PROJECT, 2018
** 104インターセッくション
** File description:
** レンダー
*/

#include "headers.h"

uint32_t rtx(demo_t *demo, dvec3 ray)
{
    /*inter_ray3 inter = octree_intersect_ray(demo->tree, (ray3){demo->cam.pos,
    ray});
    vec2 uv;

    if (inter.triangle != NULL) {
        uv = barycentric2_get_point(inter.triangle->lightmap.uv, inter.bar);
        return rgbaf32_to_uint32(texture2f_sample(
        inter.triangle->lightmap.texture, uv), _lightmaps.aperture);
    }
    else
        return 0xFF000000;*/
    (void)demo;
    (void)ray;
    return 0;
}

dvec3 dvec3_interpolate(dvec3 a, dvec3 b, long double ratio)
{
    dvec3 res;
    long double ratio_inv = 1.0L - ratio;

    res.x = a.x * ratio_inv + b.x * ratio;
    res.y = a.y * ratio_inv + b.y * ratio;
    res.z = a.z * ratio_inv + b.z * ratio;
    return (res);
}
