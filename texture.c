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

uint32_t texture2_sample(texture2 *texture, vec2 uv)
{
    size_t x = uv.x * (float)texture->w;
    size_t y = uv.y * (float)texture->h;
    ssize_t ndx = y * (ssize_t)texture->w + x;

    if (!((ndx >= 0) && (ndx < (ssize_t)texture->max_ndx)))
        return 0x000000FF;
    return swap32(texture->pixel[ndx]);
}
