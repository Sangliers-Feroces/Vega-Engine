/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static void selection_move_up(demo_t *demo)
{
    for (size_t i = 0; i < demo->editor.selections.count; i++)
        demo->editor.selections.selection[i].y += EDITOR_EXTRUSION_OFF;
}

static vec3 get_p_next(demo_t *demo, size_t i)
{
    if (i < demo->editor.selections.count - 1)
        return demo->editor.selections.selection[i + 1];
    else
        return demo->editor.selections.selection[0];
}

void editor_extrude(demo_t *demo)
{
    vec3 offset = {0.0f, EDITOR_EXTRUSION_OFF, 0.0f};
    vec3 p;
    vec3 p_next;

    if (demo->editor.selections.count < 2)
        return;
    for (size_t i = 0; i < demo->editor.selections.count ; i++) {
        p = demo->editor.selections.selection[i];
        p_next = get_p_next(demo, i);
        octree_add_triangle(&demo->tree,
        (vec3[]){p, vec3_add(p, offset), p_next});
        octree_add_triangle(&demo->tree,
        (vec3[]){p_next, vec3_add(p, offset), vec3_add(p_next, offset)});
    }
    selection_move_up(demo);
}
