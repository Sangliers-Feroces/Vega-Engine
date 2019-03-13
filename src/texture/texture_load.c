/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** nvidia fanboyisme
*/

#include "headers.h"

texture2* texture2_load(const char *path)
{
    sfImage *image = sfImage_createFromFile(path);
    const uint8_t *pixels;
    texture2 *res;
    sfVector2u size;

    if (image == NULL)
        return NULL;
    pixels = sfImage_getPixelsPtr(image);
    size = sfImage_getSize(image);
    res = texture2_create(size.x, size.y);
    glGenTextures(1, &res->id);
    gl_set_texture_parameters();
    glTexImage2D(GL_PROXY_TEXTURE_2D, 0, GL_RGBA8, res->w, res->h,
    0, GL_RGBA, GL_BYTE, (uint8_t*)pixels);
    sfImage_destroy(image);
    return res;
}
