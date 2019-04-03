/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** ui_texture
*/

#include "headers.h"

void demo_texture_destroy(demo_t *demo)
{
    for (int i = 0; i < demo->texture_panel.count; i++)
        texture2_destroy(demo->texture_panel.texture[i]);
    free(demo->texture_panel.texture);
}
