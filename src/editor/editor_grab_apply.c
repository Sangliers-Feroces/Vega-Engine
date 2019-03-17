/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static int is_point_selected(demo_t *demo, vec3 p)
{
    for (size_t i = 0; i < demo->editor.selections.count; i++)
        if (vec3_eq(demo->editor.selections.selection[i], p))
            return 1;
    return 0;
}

static int rtx_triangle_apply_delta(demo_t *demo, rtx_triangle *triangle)
{
    int has_been_modified = 0;

    for (size_t i = 0; i < 3; i++)
        if (is_point_selected(demo, triangle->vertex[i])) {
            triangle->vertex[i] =
            vec3_add(triangle->vertex[i], demo->editor.grab_delta);
            has_been_modified = 1;
        }
    return has_been_modified;
}

static void octree_apply_delta(demo_t *demo, octree *tree)
{
    if (tree == NULL)
        return;
    for (size_t i = 0; i < 8; i++)
        octree_apply_delta(demo, tree->sub[i]);
    for (size_t i = 0; i < tree->triangles.count; i++)
        if (rtx_triangle_apply_delta(demo, tree->triangles.triangle[i]))
            rtx_triangle_update(demo, tree->triangles.triangle[i]);
}

static void selection_add_delta(demo_t *demo)
{
    for (size_t i = 0; i < demo->editor.selections.count; i++)
        demo->editor.selections.selection[i] =
        vec3_add(demo->editor.selections.selection[i], demo->editor.grab_delta);
}

void editor_grab_apply(demo_t *demo)
{
    octree_apply_delta(demo, demo->tree);
    selection_add_delta(demo);
    editor_grab_replace(demo);
    texture2f_refresh_gpu(_lightmaps.base);
    demo->editor.grabbed = MODEL_EDITOR_MAX;
    demo->editor.grab_delta = (vec3){0.0f, 0.0f, 0.0f};
}
