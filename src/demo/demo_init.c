/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static void init_cam(demo_t *demo)
{
    demo->cam.pos = (vec3){0.0f, 0.0f, -5.0f};
    demo->cam.ratiowh = (long double)demo->win.w / (long double)demo->win.h;
    demo->cam.fovw = M_PI / 2.0f;
    demo->cam.near = 1.0L;
}

static int init_framebuffer(demo_t *demo)
{
    demo->win.data = (uint32_t*)malloc_safe(sizeof(uint32_t) *
    demo->win.w * demo->win.h);
    demo->win._texture = sfTexture_create(demo->win.w, demo->win.h);
    if (demo->win._texture == NULL)
        return (0);
    demo->win._sprite = sfSprite_create();
    if (demo->win._sprite == NULL)
        return (0);
    sfSprite_setTexture(demo->win._sprite, demo->win._texture, sfTrue);
    return (1);
}

static void init_win(demo_t *demo)
{
    demo->win.w = 854 / 4;
    demo->win.h = 480 / 4;
    //demo->win.w = 1920;
    //demo->win.h = 1080;
    demo->win.window = sfRenderWindow_create((sfVideoMode){demo->win.w,
    demo->win.h, 32}, "rtx on !", sfResize | sfClose, NULL);
    if (demo->win.window == NULL)
        exit_full_custom();
    sfWindow_setVerticalSyncEnabled((sfWindow*)demo->win.window, sfTrue);
    if (!init_framebuffer(demo))
        exit_full_custom();
}

demo_t* demo_init(void)
{
    demo_t *res;

    res = malloc_safe(sizeof(demo_t));
    init_win(res);
    init_cam(res);
    demo_init_input(res);
    res->tree = octree_create(NULL);
    init();
    return (res);
}

void demo_quit(demo_t *demo)
{
    quit();
    free(demo->win.data);
    sfSprite_destroy(demo->win._sprite);
    sfTexture_destroy(demo->win._texture);
    sfRenderWindow_destroy(demo->win.window);
    octree_destroy(&demo->tree);
    free(demo);
}
