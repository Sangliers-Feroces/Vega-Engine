/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** tools
*/

#include "headers.h"

static void ui_set_textures_buttons(void)
{
    _ui.buttons[UIBUTTON_MOVE].texture_index = UIRES_CROSS;
    _ui.buttons[UIBUTTON_PAINT].texture_index = UIRES_PAINT;
    _ui.buttons[UIBUTTON_TEXTURE].texture_index = UIRES_TEXTURE;
    _ui.buttons[UIBUTTON_LIGHTMAPS].texture_index = UIRES_LIGHTMAPS;
    _ui.buttons[UIBUTTON_PLAY].texture_index = UIRES_PLAY;
    _ui.buttons[UIBUTTON_ISO].texture_index = UIRES_ISO;
}

void ui_set_buttons(void)
{
    _ui.buttons[UIBUTTON_MOVE].pos = (vec2){-0.95f, 0.70f};
    _ui.buttons[UIBUTTON_MOVE].size = 0.1f;
    _ui.buttons[UIBUTTON_PAINT].pos = (vec2){-0.70f, 0.70f};
    _ui.buttons[UIBUTTON_PAINT].size = 0.1f;
    _ui.buttons[UIBUTTON_TEXTURE].pos = (vec2){-0.45f, 0.70f};
    _ui.buttons[UIBUTTON_TEXTURE].size = 0.1f;
    _ui.buttons[UIBUTTON_LIGHTMAPS].pos = (vec2){0.30f, 0.70f};
    _ui.buttons[UIBUTTON_LIGHTMAPS].size = 0.1f;
    _ui.buttons[UIBUTTON_PLAY].pos = (vec2){0.55f, 0.70f};
    _ui.buttons[UIBUTTON_PLAY].size = 0.1f;
    _ui.buttons[UIBUTTON_ISO].pos = (vec2){0.80f, 0.70f};
    _ui.buttons[UIBUTTON_ISO].size = 0.1f;
    ui_set_textures_buttons();
}

void ui_load_texture(const ui_texture_descriptor_t descriptors_array[])
{
    for (int i = 0; descriptors_array[i].path != NULL; i++)
        _ui.textures[descriptors_array[i].index] = texture2_load(descriptors_array[i].path);
}

void ui_set_textures_to_null(void)
{
    for (int i = 0; i < UIRES_MAX; i++)
        _ui.textures[i] = NULL;
}