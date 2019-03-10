/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static int poll_events(demo_t *demo)
{
    sfEvent event;

    if (!sfRenderWindow_isOpen(demo->win.window))
        return (0);
    while (sfRenderWindow_pollEvent(demo->win.window, &event))
        switch (event.type) {
            case sfEvtClosed:
            sfRenderWindow_close(demo->win.window);
            return (0);
            default:
            break;
        }
    demo_poll_input(demo);
    return (1);
}

void load_model(octree **tree);

int demo_loop(void)
{
    demo_t *demo = demo_init();

    load_model(&demo->tree);
    printf("octree done !\n");
    struct timespec start, finish;
    double elapsed;
    clock_gettime(CLOCK_MONOTONIC, &start);
    demo->cam.aperture = octree_light_rtx(demo->tree, 1000000000 / 1);
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("%f seconds\n", elapsed);
    while (poll_events(demo)) {
        sfRenderWindow_clear(demo->win.window, sfBlack);
        demo_render(demo);
        sfTexture_updateFromPixels(demo->win._texture, (uint8_t*)demo->win.data,
        demo->win.w, demo->win.h, 0, 0);
        sfRenderWindow_drawSprite(demo->win.window,
        demo->win._sprite, NULL);
        sfRenderWindow_display(demo->win.window);
    }
    demo_quit(demo);
    return (0);
}
