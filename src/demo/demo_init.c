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
    demo->player.is_grounded = 0;
    demo->player.state = GAME_EDITOR;
    demo->player.pos = (vec3){0.0f, 0.0f, 0.0f};
    demo->player.speed = (vec3){0.0f, 0.0f, 0.0f};
    demo_set_cam_to_origin(demo);
}

static int init_mouse(demo_t *demo)
{
    demo->mouse.button_state = 0;
    demo->mouse.button_release = 0;
    demo->mouse.button_click = 0;
    demo->mouse.mouse_pos = (sfVector2i){0, 0};
    return (1);
}

static void init_win(demo_t *demo)
{
    demo->win.w = 1600;
    demo->win.h = 900;
    demo->win.window = sfRenderWindow_create((sfVideoMode){demo->win.w,
    demo->win.h, 32}, "rtx on !", sfClose,
    &(sfContextSettings){24, 8, 4, 4, 3, 0, 1});
    if (demo->win.window == NULL)
        exit_full_custom();
    demo->win.frametime = sfClock_create();
    if (demo->win.frametime == NULL)
        exit_full_custom();
    demo->win.framelen = 1.0f / 60.0f;
    demo->win.has_focus = 1;
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
    _ui.button_clicked = UIBUTTON_NONE;
    demo_init_input(res);
    res->tree = octree_create(NULL);
    init();
    ui_init(res);
    demo_get_texture_pannel(res);
    editor_init(res);
    gl_gen(res);
    return (res);
}

void demo_quit(demo_t *demo)
{
    editor_quit(demo);
    octree_destroy(&demo->tree);
    demo_texture_destroy(demo);
    gl_delete(demo);
    ui_quit();
    texture2f_write(_lightmaps.base, _lightmaps.aperture);
    quit();
    sfRenderWindow_destroy(demo->win.window);
    sfClock_destroy(demo->win.frametime);
    free(demo);
}
