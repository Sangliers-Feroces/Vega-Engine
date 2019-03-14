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
        demo->mouse.mouse_pos =
        sfMouse_getPositionRenderWindow(demo->win.window);
        demo->mouse.first_click = 1;
        ui_check_click_button(demo);
        break;
    case sfEvtMouseButtonReleased:
        demo->mouse.first_click = 0;
        break;
    default:
        break;
    }
    return (1);
}

int poll_events(demo_t *demo)
{
    sfEvent event;

    if (!sfRenderWindow_isOpen(demo->win.window))
        return (0);
    while (sfRenderWindow_pollEvent(demo->win.window, &event))
        if (!do_stuff_event(demo, event))
            return (0);
    check_mouse_move(demo);
    demo_poll_input(demo);
    return (1);
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
    demo->cam.aperture = octree_light_rtx(demo->tree, 50);
    printf("aperture: %f\n", demo->cam.aperture);
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("%f seconds\n", elapsed);
    demo_loop(demo);
    demo_quit(demo);
    return (0);
}
