/*
** EPITECH PROJECT, 2018
** 104インターセッくション
** File description:
** レンダー
*/

#include "headers.h"

static uint32_t rbaf32_to_uint32(vec3 rgb, float aperture)
{
    uint32_t r = MIN(rgb.x / aperture * 255.0f, 255.0f);
    uint32_t g = MIN(rgb.y / aperture * 255.0f, 255.0f);
    uint32_t b = MIN(rgb.z / aperture * 255.0f, 255.0f);

    return 0xFF000000 | (b << 16) | (g << 8) | r;
}

static uint32_t rtx(demo_t *demo, vec3 ray)
{
    inter_ray3 inter = octree_intersect_ray(demo->tree, (ray3){demo->cam.pos,
    ray});
    vec2 uv;

    if (inter.triangle != NULL) {
        uv = barycentric2_get_point(inter.triangle->lightmap.uv, inter.bar);
        return rbaf32_to_uint32(
        texture2f_sample(inter.triangle->lightmap.texture, uv), demo->cam.aperture);
    }
    else
        return 0xFF000000;
}

vec3 get_plane(demo_t *demo, vec3 *top_left, vec3 *top_right,
vec3 *bottom_left)
{
    vec3 res = {-demo->cam.near,
    demo->cam.near / (long double)demo->cam.ratiowh, demo->cam.near};

    *top_left = res;
    *top_right = (vec3){-res.x, res.y, res.z};
    *bottom_left = (vec3){res.x, -res.y, res.z};
    return (vec3){-res.x, -res.y, res.z};
}

vec3 interpolate_vec3(vec3 a, vec3 b, long double ratio)
{
    vec3 res;
    long double ratio_inv = 1.0L - ratio;

    res.x = a.x * ratio_inv + b.x * ratio;
    res.y = a.y * ratio_inv + b.y * ratio;
    res.z = a.z * ratio_inv + b.z * ratio;
    return (res);
}

void demo_render(demo_t *demo)
{
    vec3 tl;
    vec3 tr;
    vec3 bl;
    vec3 br;
    long double ratiox;
    long double ratioy;

    br = get_plane(demo, &tl, &tr, &bl);
    for (int64_t i = 0; i < demo->win.h; i++)
        for (int64_t j = 0; j < demo->win.w; j++) {
            ratiox = (long double)j / (long double)(demo->win.w - 1);
            ratioy = (long double)i / (long double)(demo->win.h - 1);
            demo->win.data[i * demo->win.w + j] =
            rtx(demo, interpolate_vec3(interpolate_vec3(tl, tr, ratiox),
            interpolate_vec3(bl, br, ratiox), ratioy));
        }
}
