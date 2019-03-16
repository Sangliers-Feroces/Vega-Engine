/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

void editor(demo_t *demo)
{
    inter_ray3 inter;

    demo_refresh_viewport(demo);
    if (_ui.button_clicked != UIBUTTON_NONE)
        return;
    inter = octree_intersect_ray(demo->tree, demo_get_ray(demo));
    switch (demo->action) {
    case ACTION_MOVE:
        if (demo->mouse.button_click & (1 << sfMouseLeft))
            editor_select(demo, inter);
    printf("selected: %zu\n", demo->editor.selections.count);
        break;
    case ACTION_PAINT:
        if (demo->mouse.button_state & (1 << sfMouseLeft))
            editor_paint(demo, inter);
        break;
    }
}
