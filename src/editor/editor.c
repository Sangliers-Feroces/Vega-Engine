/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static void editor_shortcut(demo_t *demo)
{
    if (demo->input.key_press['P'])
        _ui.display_ui = !_ui.display_ui;
}

void editor(demo_t *demo)
{
    inter_ray3 inter;

    if (!demo->win.has_focus)
        return;
    editor_shortcut(demo);
    demo_refresh_viewport(demo);
    if (_ui.button_hovered != UIBUTTON_NONE)
        return;
    demo->mouse.ray = demo_get_ray(demo);
    inter = octree_intersect_ray(demo->tree, demo->mouse.ray);
    switch (demo->action) {
    case ACTION_MOVE:
        editor_select(demo, inter);
        break;
    case ACTION_PAINT:
        if (demo->mouse.button_state & (1 << sfMouseLeft))
            editor_paint(demo, inter);
        break;
    }
}
