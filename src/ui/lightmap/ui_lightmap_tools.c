/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** ui_lightmap_tools
*/

#include "headers.h"

void ui_lm_set_texture_array(ui_lm_struct_t *ui_lm_struct,
const ui_lm_tex_desc_t texture_desc_array[])
{
    for (int i = 0; i < UILIGHTMAP_END; i++)
        ui_lm_struct->textures[i] = NULL;
    for (int i = 0; texture_desc_array[i].path != NULL; i++)
        ui_lm_struct->textures[i] =
        texture2_load(texture_desc_array[i].path);
}