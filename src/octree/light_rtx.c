/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** optiiiiiii rtx
*/

#include "headers.h"

/*static dvec3 diffuse_ray(rtx_triangle *triangle)
{
    float n = 1.0f;
    float x = 2.0f * M_PI * randf();
    float y = acosf(powf(randf(), 1.0f / (n + 1.0f)));

    return dvec3_add(dvec3_add(
    dvec3_muls(triangle->tangent, sinf(y) * cosf(x)),
    dvec3_muls(triangle->bitangent, sinf(y) * sinf(x))),
    dvec3_muls(triangle->normal, cosf(y)));
}*/

void octree_throw_ray(octree *tree, ray3_color ray)
{
    (void)tree;
    (void)ray;
    /*inter_ray3 inter = octree_intersect_ray(tree, ray.ray);

    if (inter.triangle == NULL)
        return;
    texture2f_write_color_bar(inter.triangle->lightmap.texture,
    inter.triangle->lightmap.uv, inter.bar, ray.color);
    if ((--ray.count) == 0)
        return;
    else
        octree_throw_ray(tree,
        (ray3_color){(ray3){inter.p, diffuse_ray(inter.triangle)},
        dvec3_muls(ray.color, 0.75f), ray.count});*/
}

float octree_light_rtx(octree *tree, size_t density)
{
    (void)tree;
    (void)density;
    /*octree_reset_lumels(tree);
    thread_send_each(THREAD_TASK_RAY_TRACING,
    (uint64_t[]){(uint64_t)tree, density / _thread.count}, 2);
    thread_wait();
    texture2f_refresh_gpu(_lightmaps.base);
    return (octree_get_max_lumel(tree) / 3.0f) / 2.0f;*/
    return 0.0f;
}
