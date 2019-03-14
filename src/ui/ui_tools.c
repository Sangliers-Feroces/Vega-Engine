/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** tools
*/

#include "headers.h"

void ui_set_buttons(void)
{
    _ui.buttons[UIBUTTON_MOVE] =
    (button_t){UIRES_CROSS, (vec2){-0.95f, 0.70f}, 0.1f, BUTTON_REL_X};
    _ui.buttons[UIBUTTON_PAINT] =
    (button_t){UIRES_PAINT, (vec2){-0.70f, 0.70f}, 0.1f, BUTTON_REL_X};
    _ui.buttons[UIBUTTON_TEXTURE] =
    (button_t){UIRES_TEXTURE, (vec2){-0.45f, 0.70f}, 0.1f, BUTTON_REL_X};
    _ui.buttons[UIBUTTON_LIGHTMAPS] =
    (button_t){UIRES_LIGHTMAPS, (vec2){0.30f, 0.70f}, 0.1f, BUTTON_REL_X};
    _ui.buttons[UIBUTTON_PLAY] =
    (button_t){UIRES_PLAY, (vec2){0.55f, 0.70f}, 0.1f, BUTTON_REL_X};
    _ui.buttons[UIBUTTON_ISO] =
    (button_t){UIRES_ISO, (vec2){0.80f, 0.70f}, 0.1f, BUTTON_REL_X};
}

void ui_load_texture(const ui_texture_descriptor_t descriptors_array[])
{
    for (int i = 0; descriptors_array[i].path != NULL; i++)
        _ui.textures[descriptors_array[i].index] =
        texture2_load(descriptors_array[i].path);
}

void ui_set_textures_to_null(void)
{
    for (int i = 0; i < UIRES_MAX; i++)
        _ui.textures[i] = NULL;
}
