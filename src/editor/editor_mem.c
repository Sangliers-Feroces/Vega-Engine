/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

void editor_init(demo_t *demo)
{
    demo->editor.selections = (vec_selection_t){0, 0, NULL};
}

void editor_quit(demo_t *demo)
{
    free(demo->editor.selections.selection);
}
