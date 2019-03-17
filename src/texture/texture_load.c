/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** nvidia fanboyisme
*/

#include "headers.h"

static int get_pannel_count(void)
{
    int count = 0;
    struct dirent *read;
    DIR *rep = opendir("res/textures");

    if (rep == NULL)
        return 0;
    while ((read = readdir(rep)) != NULL) {
        if (read->d_name[0] == '.')
            continue;
        count++;
    }
    closedir(rep);
    return count;
}

char *get_texture_path(char *name)
{
    int j = 0;
    int name_size = my_strlen(name);
    char path_front[] = "res/textures/";
    char *res;

    res = malloc_safe(14 + name_size);
    for (int i = 0; i < 13; i++) {
        res[j] = path_front[i];
        j++;
    }
    for (int i = 0; i < name_size; i++) {
        res[j] = name[i];
        j++;
    }
    res[j] = '\0';
    return res;
}

static void ensure_textures(demo_t *demo)
{
    if (demo->texture_panel.count == 0) {
        my_fd_putstr("Error no texture\n", 2);
        exit(84);
    }
}

demo_t *demo_get_texture_pannel(demo_t *demo)
{
    struct dirent *read;
    DIR *rep = opendir("res/textures");
    char *path;

    demo->texture_panel.count = get_pannel_count();
    ensure_textures(demo);
    demo->texture_panel.texture =
    malloc_safe((sizeof(texture2*) * demo->texture_panel.count));
    for (int i = 0; i < demo->texture_panel.count; i++) {
        read = readdir(rep);
        if (read->d_name[0] == '.') {
            i--;
            continue;
        }
        path = get_texture_path(read->d_name);
        demo->texture_panel.texture[i] = texture2_load(path);
        free(path);
    }
    closedir(rep);
    return demo;
}

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
    glBindTexture(GL_TEXTURE_2D, res->id);
    gl_set_texture_parameters();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, res->w, res->h,
    0, GL_RGBA, GL_UNSIGNED_BYTE, (uint8_t*)pixels);
    sfImage_destroy(image);
    return res;
}
