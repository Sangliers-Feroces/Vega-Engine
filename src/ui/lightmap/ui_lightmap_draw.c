/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** ui_lightmap_draw
*/

#include "headers.h"

void ui_lightmap_draw(void)
{
    for (int i = 0; i < UILMBUTTON_END; i++) {
        button_draw(_ui.ui_lightmap_struct.object[i]);
    }
}