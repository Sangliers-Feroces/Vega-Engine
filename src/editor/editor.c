/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

void demo_update_cursor_visibility(demo_t *demo)
{
    sfWindow_setMouseCursorVisible((sfWindow*)demo->win.window,
    _iu.data.is_invent);
}

void demo_center_cursor(demo_t *demo)
{
    sfMouse_setPosition((sfVector2i){demo->win.w / 2, demo->win.h / 2},
    (sfWindow*)demo->win.window);
}

static void editor_shortcut(demo_t *demo)
{
    if (demo->input.key_press['N']) {
        demo->player.state = !demo->player.state;
        demo->player.pos = demo->cam.pos;
    }
    if (demo->input.key_press['E']) {
        _iu.data.is_invent = !_iu.data.is_invent;
        if (_iu.data.is_invent)
            demo_center_cursor(demo);
        demo_update_cursor_visibility(demo);
    }
}

void editor(demo_t *demo)
{
    if (!demo->win.has_focus)
        return;
    editor_shortcut(demo);
}
