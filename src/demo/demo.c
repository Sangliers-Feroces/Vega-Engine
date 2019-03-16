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
    check_mouse_move(demo);
    demo_poll_input(demo);
    if (demo->mouse.button_click & (1 << sfMouseLeft))
        ui_check_click_button(demo);
    return (1);
}

void demo_loop(demo_t *demo)
{
    while (poll_events(demo)) {
        editor(demo);
        demo_render_geom(demo);
        editor_draw(demo);
        ui_display(1, demo);
        sfRenderWindow_display(demo->win.window);
    }
}

int demo(void)
{
    demo_t *demo = demo_init();

    glEnable(GL_MULTISAMPLE);
    load_model(&demo->tree);
    printf("octree done !\n");
    struct timespec start, finish;
    double elapsed;
    clock_gettime(CLOCK_MONOTONIC, &start);
    demo->cam.aperture = octree_light_rtx(demo->tree, 10);
    printf("aperture: %f\n", demo->cam.aperture);
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("%f seconds\n", elapsed);
    demo_loop(demo);
    demo_quit(demo);
    return (0);
}
