/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static int do_stuff_event(demo_t *demo, sfEvent event)
{
    switch (event.type) {
    case sfEvtClosed:
        sfRenderWindow_close(demo->win.window);
        return (0);
    case sfEvtMouseButtonPressed:
        demo->mouse.button_state |= (1 << event.mouseButton.button);
        break;
    case sfEvtMouseButtonReleased:
        demo->mouse.button_state &= ~(1 << event.mouseButton.button);
        break;
    case sfEvtGainedFocus:
        demo->win.has_focus = 1;
        break;
    case sfEvtLostFocus:
        demo->win.has_focus = 0;
        break;
    default:
        break;
    }
    return (1);
}

static void poll_click(demo_t *demo)
{
    demo->mouse.button_click = 0;
    for (size_t i = 0; i < 16; i++)
        demo->mouse.button_click |=
        ((((demo->mouse.button_state >> i) & 1) == 1) &&
        (((demo->mouse.button_last >> i) & 1) == 0)) << i;
    demo->mouse.button_release = 0;
    for (size_t i = 0; i < 16; i++)
        demo->mouse.button_release |=
        ((((demo->mouse.button_state >> i) & 1) == 0) &&
        (((demo->mouse.button_last >> i) & 1) == 1)) << i;
}

void demo_refresh_mouse_pos(void)
{
    _demo->mouse.last_pos = _demo->mouse.mouse_pos;
    _demo->mouse.mouse_pos = sfMouse_getPositionRenderWindow(_demo->win.window);
}

static void poll_mouse_pos(demo_t *demo)
{
    int do_tp = 0;

    if (!demo->win.has_focus)
        return;
    demo_refresh_mouse_pos();
    if (_iu.data.is_focus)
        return;
    if ((ssize_t)demo->mouse.mouse_pos.x < (ssize_t)(demo->win.w / 4)) {
        demo->mouse.mouse_pos.x += demo->win.w / 2;
        demo->mouse.last_pos.x += demo->win.w / 2;
        do_tp = 1;
    }
    if ((ssize_t)demo->mouse.mouse_pos.x > (ssize_t)(demo->win.w * 3 / 4)) {
        demo->mouse.mouse_pos.x -= demo->win.w / 2;
        demo->mouse.last_pos.x -= demo->win.w / 2;
        do_tp = 1;
    }
    if ((ssize_t)demo->mouse.mouse_pos.y < (ssize_t)(demo->win.h / 4)) {
        demo->mouse.mouse_pos.y += demo->win.h / 2;
        demo->mouse.last_pos.y += demo->win.h / 2;
        do_tp = 1;
    }
    if ((ssize_t)demo->mouse.mouse_pos.y > (ssize_t)(demo->win.h * 3 / 4)) {
        demo->mouse.mouse_pos.y -= demo->win.h / 2;
        demo->mouse.last_pos.y -= demo->win.h / 2;
        do_tp = 1;
    }
    if (do_tp)
        sfMouse_setPosition((sfVector2i){demo->mouse.mouse_pos.x,
        demo->mouse.mouse_pos.y}, (sfWindow*)demo->win.window);
}

int poll_events(demo_t *demo)
{
    sfEvent event;

    if (!sfRenderWindow_isOpen(demo->win.window))
        return (0);
    while (sfRenderWindow_pollEvent(demo->win.window, &event))
        if (!do_stuff_event(demo, event))
            return (0);
    if (!demo->win.has_focus)
        return (1);
    demo->mouse.button_last = demo->mouse.button_state;
    poll_mouse_pos(demo);
    poll_click(demo);
    check_mouse_move(demo);
    demo_poll_input(demo);
    return (1);
}

void demo_loop(demo_t *demo)
{
    while (poll_events(demo)) {
        demo_update_cursor_visibility(demo);
        demo->game_time = get_eleapsed_time_second(demo->clocks.game_clock);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        editor(demo);
        world_update();
        world_render();
        iu_display();
        sfRenderWindow_display(demo->win.window);
    }
}

int demo(arg_t args)
{
    demo_t *demo = demo_init();

    (void)args;
    if (!start(demo)) {
        demo_quit(demo);
        return 0;
    }
    demo_loop(demo);
    demo_quit(demo);
    return (0);
}
