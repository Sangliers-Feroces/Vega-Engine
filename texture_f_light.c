/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** nvidia fanboyisme
*/

#include "headers.h"

float texture2f_get_max_lumel(texture2f *texture)
{
    float cur = 0.0f;
    float sum;

    for (size_t i = 0; i < texture->max_ndx; i++) {
        sum = texture->pixel[i].r + texture->pixel[i].g + texture->pixel[i].b;
        if (sum > cur)
            cur = sum;
    }
    return cur;
}

static uint32_t get_byte(float value)
{
    return CLAMP(value, 0.0f, 255.0f);
}

void texture_update_lightmap(texture2f *src, texture2 *dst, float max_lumel)
{
    if (!((src->w == dst->w) && (src->h == dst->h)))
        return;
    for (size_t i = 0; i < src->max_ndx; i++)
        dst->pixel[i] = get_byte(src->pixel[i].r / max_lumel) << 24 |
        get_byte(src->pixel[i].g / max_lumel) << 16 |
        get_byte(src->pixel[i].b / max_lumel) << 8 | 0xFF;
}
