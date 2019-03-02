/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** optiiiiiii rtx
*/

#include "headers.h"

static vec3 diffuse_ray(rtx_triangle *triangle)
{
    float n = 1.0f;
    float x = 2.0f * M_PI * randf();
    float y = acosf(powf(randf(), 1.0f / (n + 1.0f)));

    return vec3_add(vec3_add(
    vec3_muls(triangle->tangent, sinf(y) * cosf(x)),
    vec3_muls(triangle->bitangent, sinf(y) * sinf(x))),
    vec3_muls(triangle->normal, cosf(y)));
}

static void throw_ray(octree *tree, ray3_color ray)
{
    inter_ray3 inter = octree_intersect_ray(tree, ray.ray);

    if (inter.triangle == NULL)
        return;
    texture2f_write_color_bar(inter.triangle->lumels,
    inter.triangle->lightmap.uv, inter.bar, ray.color);
    if ((--ray.count) == 0)
        return;
    else
        throw_ray(tree,
        (ray3_color){(ray3){inter.p, diffuse_ray(inter.triangle)},
        vec3_muls(ray.color, 0.75f), ray.count});
}

void octree_light_rtx_thread(octree *tree, size_t rays)
{
    for (size_t i = 0; i < rays; i++) {
        throw_ray(tree, (ray3_color){
        {{randf() * 100.0f - 50.0f, 50.0f, -randf() * 100.0f},
        {1.0f, -1.0f, 1.0f}}, {1.0f, 1.0f, 1.0f}, 16});
    }
}

void octree_light_rtx(octree *tree, size_t rays)
{
    octree_reset_lumels(tree);
    thread_send_each(THREAD_TASK_RAY_TRACING,
    (uint64_t[]){(uint64_t)tree, rays / _thread.count}, 2);
    thread_wait();
    //octree_light_rtx_thread(tree, rays);
    octree_update_lightmap(tree,
    MAX((octree_get_max_lumel(tree) / 3.0f), 1.0f) / 8.0f);
}
