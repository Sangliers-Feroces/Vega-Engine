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

int poll_events(demo_t *demo)
{
    sfEvent event;

    demo->mouse.button_last = demo->mouse.button_state;
    demo->mouse.last_pos = demo->mouse.mouse_pos;
    demo->mouse.mouse_pos = sfMouse_getPositionRenderWindow(demo->win.window);
    if (!sfRenderWindow_isOpen(demo->win.window))
        return (0);
    while (sfRenderWindow_pollEvent(demo->win.window, &event))
        if (!do_stuff_event(demo, event))
            return (0);
    poll_click(demo);
    if (!demo->win.has_focus)
        return (1);
    check_mouse_move(demo);
    demo_poll_input(demo);
    return (1);
}

void demo_loop(demo_t *demo)
{
    sfMusic *music = sfMusic_createFromFile("res/musics/main_music.ogg");

    sfMusic_play(music);
    sfMusic_setLoop(music, sfTrue);
    dungeons_gen_all(demo, 2);
    while (poll_events(demo)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        editor(demo);
        demo_render_geom(demo);
        world_render(demo);
        editor_draw(demo);
        sfRenderWindow_display(demo->win.window);
    }
    sfMusic_stop(music);
    sfMusic_destroy(music);
}

int demo(arg_t args)
{
    demo_t *demo = demo_init();

    (void)args;
    if (!start(demo)) {
        demo_quit(demo);
        return 0;
    }
    //terrain_gen(demo, args.size, args.iter, args.strenght);
    demo_loop(demo);
    demo_quit(demo);
    return (0);
}
