/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

int rtx_triangle_is_selected(demo_t *demo, rtx_triangle *triangle)
{
    for (size_t i = 0; i < 3; i++)
        if (!editor_is_point_selected(demo, triangle->vertex[i]))
            return 0;
    return 1;
}

void editor_flip(demo_t *demo)
{
    (void)demo;
}
