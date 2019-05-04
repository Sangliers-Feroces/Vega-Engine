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

int demo_poll_events(demo_t *demo)
{
    sfEvent event;

    if (!sfRenderWindow_isOpen(demo->win.window))
        return (0);
    demo->mouse.button_last = demo->mouse.button_state;
    while (sfRenderWindow_pollEvent(demo->win.window, &event))
        if (!do_stuff_event(demo, event))
            return (0);
    if (!demo->win.has_focus)
        return (1);
    demo_poll_mouse_pos(demo);
    poll_click(demo);
    demo_poll_input(demo);
    refresh_sound_volume();
    return (1);
}
