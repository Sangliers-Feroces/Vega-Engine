/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** nvidia fanboyisme
*/

#include "headers.h"

texture2f* texture2f_create(uint32_t w, uint32_t h)
{
    texture2f *res = (texture2f*)malloc_safe(sizeof(texture2f));

    res->w = w;
    res->h = h;
    res->max_ndx = res->w * res->h;
    res->pixel = (vec3*)malloc_safe(w * h * sizeof(vec3));
    return res;
}

void texture2f_destroy(texture2f *texture)
{
    free(texture->pixel);
    free(texture);
}

void texture2f_reset(texture2f *texture)
{
    memset(texture->pixel, 0, texture->w * texture->h * sizeof(vec3));
}

static void write_color(texture2f *texture, ssize_t x, ssize_t y, vec3 color)
{
    ssize_t ndx = y * (ssize_t)texture->w + x;
    vec3 *to_mod;

    if (!((ndx >= 0) && (ndx < (ssize_t)texture->max_ndx)))
        return;
    to_mod = &texture->pixel[ndx];
    *to_mod = vec3_add(*to_mod, color);
}

void texture2f_write_color_bar(texture2f *texture, vec2 *uv, vec3 bar,
vec3 color)
{
    vec2 p = barycentric2_get_point(uv, bar);
    size_t x;
    size_t y;

    texture2_get_nearest(p, (vec2){(float)texture->w, (float)texture->h},
    &x, &y);
    write_color(texture, x, y, color);
    write_color(texture, x - 1, y, vec3_muls(color, 0.5f));
    write_color(texture, x + 1, y, vec3_muls(color, 0.5f));
    write_color(texture, x, y - 1, vec3_muls(color, 0.5f));
    write_color(texture, x, y + 1, vec3_muls(color, 0.5f));
    write_color(texture, x - 1, y - 1, vec3_muls(color, 0.33f));
    write_color(texture, x + 1, y - 1, vec3_muls(color, 0.33f));
    write_color(texture, x - 1, y + 1, vec3_muls(color, 0.33f));
    write_color(texture, x + 1, y + 1, vec3_muls(color, 0.33f));
}
