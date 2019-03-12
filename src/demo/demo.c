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

int demo_loop(void)
{
    demo_t *demo = demo_init();
    vertex_struct_t v_struct;

    glEnable(GL_MULTISAMPLE);
    load_model(&demo->tree);
    printf("octree done !\n");
    struct timespec start, finish;
    double elapsed;
    clock_gettime(CLOCK_MONOTONIC, &start);
    demo->cam.aperture = octree_light_rtx(demo->tree, 1000000000 / 5000);
    printf("%f\n", demo->cam.aperture);
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("%f seconds\n", elapsed);
    v_struct = get_vertex_array_from_octree(demo);
    display_vertex_array(demo, v_struct);
    free(v_struct.v_array);
    demo_quit(demo);
    return (0);
}
