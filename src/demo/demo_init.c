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
    demo->cam.rot = (vec3){0.0f, 0.0f, 0.0f};
    demo->cam.ratiowh = (long double)demo->win.w / (long double)demo->win.h;
    demo->cam.fovw = M_PI / 2.0f;
    demo->cam.near = 1.0L;
    demo->cam.proj = PROJ_TYPE_PERSPECTIVE;
}

static int init_mouse(demo_t *demo)
{
    demo->mouse.first_click = 0;
    demo->mouse.mouse_pos = (sfVector2i){0, 0};
    return (1);
}

static void init_win(demo_t *demo)
{
    demo->win.w = 1600;
    demo->win.h = 900;
    demo->win.window = sfRenderWindow_create((sfVideoMode){demo->win.w,
    demo->win.h, 32}, "rtx on !", sfResize | sfClose,
    &(sfContextSettings){24, 8, 4, 4, 3, 0, 1});
    if (demo->win.window == NULL)
        exit_full_custom();
    sfWindow_setVerticalSyncEnabled((sfWindow*)demo->win.window, sfTrue);
    if (!init_mouse(demo))
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
    ui_init(res);
    return (res);
}

void demo_quit(demo_t *demo)
{
    ui_quit();
    quit();
    sfRenderWindow_destroy(demo->win.window);
    octree_destroy(&demo->tree);
    free(demo);
}
