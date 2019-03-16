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
    if (!(demo->mouse.button_state & (1 << sfMouseLeft)))
        return;
    inter = octree_intersect_ray(demo->tree, demo_get_ray(demo));
    switch (demo->action) {
    case ACTION_MOVE:
        editor_select(demo, inter);
        break;
    case ACTION_PAINT:
        editor_paint(demo, inter);
        break;
    }
}
