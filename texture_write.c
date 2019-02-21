/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** nvidia fanboyisme
*/

#include "headers.h"

static size_t align_up(size_t addr, size_t align)
{
    size_t extra = addr % align;

    if (extra == 0)
        return addr;
    else
        return addr + align - extra;
}

static void write_header(texture2 *texture, char *data, size_t size,
size_t pitch)
{
    data[0x00] = 'B';
    data[0x01] = 'M';
    *((uint32_t*)(data + 0x02)) = size;
    *((uint32_t*)(data + 0x0A)) = 60;
    *((uint32_t*)(data + 0x0E)) = 40;
    *((uint32_t*)(data + 0x12)) = texture->w;
    *((uint32_t*)(data + 0x16)) = texture->h;
    *((uint16_t*)(data + 0x1A)) = 1;
    *((uint16_t*)(data + 0x1C)) = 24;
    *((uint32_t*)(data + 0x1E)) = 0;
    *((uint32_t*)(data + 0x22)) = pitch;
    *((uint32_t*)(data + 0x26)) = 0;
    *((uint32_t*)(data + 0x2A)) = 0;
    *((uint32_t*)(data + 0x2E)) = 0;
    *((uint32_t*)(data + 0x32)) = 0;
}

static void write_data(texture2 *texture, char *dst, size_t pitch)
{
    for (size_t i = 0; i < texture->h; i++)
        for (size_t j = 0; j < texture->w; j++) {
            dst[i * pitch + j * 3] =
            (texture->pixel[i * texture->w + j] >> 8) & 0xFF;
            dst[i * pitch + j * 3 + 1] =
            (texture->pixel[i * texture->w + j] >> 16) & 0xFF;
            dst[i * pitch + j * 3 + 2] =
            (texture->pixel[i * texture->w + j] >> 24) & 0xFF;
        }
}

static void write_file(const char *data, size_t size, void *ptr)
{
    char path[512];
    FILE *file;

    sprintf(path, "lightmaps/%p.bmp", ptr);
    file = fopen(path, "wb+");
    if (file == NULL)
        return;
    fwrite(data, sizeof(char), size, file);
    fclose(file);
}

void texture2_write(texture2 *texture)
{
    size_t pitch = align_up(texture->w * 3, 4);
    size_t size = 60 + pitch * texture->h;
    char *data = (char*)malloc_safe(size);

    memset(data, 0, size);
    write_header(texture, data, size, pitch);
    write_data(texture, &data[60], pitch);
    write_file(data, size, texture);
    free(data);
}
