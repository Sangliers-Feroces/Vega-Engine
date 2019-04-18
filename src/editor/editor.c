/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static void editor_shortcut(demo_t *demo)
{
    if (demo->input.key_press['N']) {
        demo->player.state = !demo->player.state;
        demo->player.pos = demo->cam.pos;
    }
    if (demo->input.key_press['E']) {
        _iu.data.is_invent = !_iu.data.is_invent;
    }
}

void editor(demo_t *demo)
{
    if (!demo->win.has_focus)
        return;
    editor_shortcut(demo);
}
