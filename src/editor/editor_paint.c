/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

void editor_paint(demo_t *demo, inter_ray3 inter)
{
    if (inter.triangle == NULL)
        return;
    printf("got: %p\n", inter.triangle->albelo.texture);
    inter.triangle->albelo.texture =
    demo->texture_panel.texture[_ui.selected_texture];
}
