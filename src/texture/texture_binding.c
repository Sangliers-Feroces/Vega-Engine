/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** nvidia fanboyisme
*/

#include "headers.h"

static vec2 get_uv(vec2 vec, vec2 dim, float scale)
{
    return (vec2){(vec.x * scale) / dim.x, (vec.y * scale) / dim.y};
}

texture2_binding texture2_binding_create(vec3 *triangle)
{
    texture2_binding res = {.is_linked = 1};
    vec2 min;
    vec2 max;
    vec2 dim;
    float scale = 8.0f;

    res.uv[0] = (vec2){0.0f, 0.0f};
    res.uv[1] = (vec2){vec3_dist(triangle[0], triangle[1]), 0.0f};
    res.uv[2] = circle_intersect(
    (circle){res.uv[0], vec3_dist(triangle[0], triangle[2])},
    (circle){res.uv[1], vec3_dist(triangle[1], triangle[2])});
    min = vec2_min(vec2_min(res.uv[0], res.uv[1]), res.uv[2]);
    max = vec2_max(vec2_max(res.uv[0], res.uv[1]), res.uv[2]);
    dim = vec2_muls(vec2_sub(max, min), scale);
    res.texture = texture2_create((uint32_t)dim.x + 1, (uint32_t)dim.y + 1);
    for (size_t i = 0; i < 3; i++)
        res.uv[i] = get_uv(vec2_sub(res.uv[i], min), dim, scale);
    return res;
}

void texture2_binding_destroy(texture2_binding binding)
{
    if (binding.is_linked) {
        printf("%u, %u\n", binding.texture->w, binding.texture->h);
        texture2_destroy(binding.texture);
    }
}
