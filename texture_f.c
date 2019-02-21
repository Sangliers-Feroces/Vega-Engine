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
    res->pixel = (pixelf*)malloc_safe(w * h * sizeof(pixelf));
    return res;
}

void texture2f_destroy(texture2f *texture)
{
    free(texture->pixel);
    free(texture);
}

void texture2f_reset(texture2f *texture)
{
    memset(texture->pixel, 0, texture->w * texture->h * sizeof(pixelf));
}
