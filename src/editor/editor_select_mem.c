/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

void editor_select_point(demo_t *demo, dvec3 p)
{
    size_t cur = demo->editor.selections.count++;
    dvec3 *new_select;

    if (demo->editor.selections.count > demo->editor.selections.allocated) {
        demo->editor.selections.allocated += 16;
        new_select =
        (dvec3*)malloc_safe(demo->editor.selections.allocated * sizeof(dvec3));
        for (size_t i = 0; i < cur; i++)
            new_select[i] = demo->editor.selections.selection[i];
        free(demo->editor.selections.selection);
        demo->editor.selections.selection = new_select;
    }
    demo->editor.selections.selection[cur] = p;
}

void editor_remove_point(demo_t *demo, dvec3 p)
{
    for (size_t i = 0; i < demo->editor.selections.count; i++)
        if (dvec3_eq(demo->editor.selections.selection[i], p)) {
            demo->editor.selections.count--;
            demo->editor.selections.selection[i] =
            demo->editor.selections.selection[demo->editor.selections.count];
            return;
        }
}
