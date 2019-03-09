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

int demo_loop(octree *tree)
{
    demo_t *demo = demo_init(tree);

    glint lol;
	glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &lol);
    printf("max: %d\n", lol);
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
