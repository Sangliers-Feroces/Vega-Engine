/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

int editor_is_point_selected(demo_t *demo, vec3 p)
{
    for (size_t i = 0; i < demo->editor.selections.count; i++)
        if (vec3_eq(demo->editor.selections.selection[i], p))
            return 1;
    return 0;
}

static int rtx_triangle_try_delete(demo_t *demo, octree *tree,
rtx_triangle *triangle)
{
    for (size_t i = 0; i < 3; i++)
        if (editor_is_point_selected(demo, triangle->vertex[i])) {
            octree_rtx_triangle_detach(tree, triangle);
            rtx_triangle_destroy(triangle);
            return 1;
        }
    return 0;
}

static void del_rec(demo_t *demo, octree *tree)
{
    if (tree == NULL)
        return;
    for (size_t i = 0; i < 8; i++)
        del_rec(demo, tree->sub[i]);
    for (size_t i = 0; i < tree->triangles.count; i++)
        if (rtx_triangle_try_delete(demo, tree, tree->triangles.triangle[i]))
            i--;
}

void editor_del(demo_t *demo)
{
    del_rec(demo, demo->tree);
    demo->editor.selections.count = 0;
}
