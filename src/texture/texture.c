/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** nvidia fanboyisme
*/

#include "headers.h"

texture2* texture2_create(uint32_t w, uint32_t h)
{
    texture2 *res = (texture2*)malloc_safe(sizeof(texture2));

    res->w = w;
    res->h = h;
    res->max_ndx = res->w * res->h;
    res->pixel = (uint32_t*)malloc_safe(w * h * sizeof(uint32_t));
    return res;
}

void texture2_destroy(texture2 *texture)
{
    free(texture->pixel);
    free(texture);
}

ivec2 texture2_get_nearest(vec2 p, vec2 size)
{
    p = vec2_add(vec2_mul(p, size), (vec2){0.5f, 0.5f});
    return (ivec2){p.x, p.y};
}

uint32_t texture2_sample(texture2 *texture, vec2 uv)
{
    ivec2 pos;
    ssize_t ndx;

    pos = texture2_get_nearest(
    uv, (vec2){(float)texture->w, (float)texture->h});
    ndx = pos.y * (ssize_t)texture->w + pos.x;
    if (!((ndx >= 0) && (ndx < (ssize_t)texture->max_ndx)))
        return 0x000000FF;
    return swap32(texture->pixel[ndx]);
}

vec4 texture2f_sample(texture2f *texture, vec2 uv)
{
    ivec2 pos;
    ssize_t ndx;

    pos = texture2_get_nearest(uv, texture->size);
    ndx = pos.y * (ssize_t)texture->w + pos.x;
    if (!((ndx >= 0) && (ndx < (ssize_t)texture->max_ndx)))
        return (vec4){0.0f, 0.0f, 0.0f, 0.0f};
    return texture->pixel[ndx];
}
