/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

int editor_is_point_selected(demo_t *demo, dvec3 p)
{
    for (size_t i = 0; i < demo->editor.selections.count; i++)
        if (dvec3_eq(demo->editor.selections.selection[i], p))
            return 1;
    return 0;
}

void editor_del(demo_t *demo)
{
    (void)demo;
}
