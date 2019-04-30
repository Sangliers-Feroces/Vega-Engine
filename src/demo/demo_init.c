/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static void init_cam(demo_t *demo)
{
    demo->cam.ratiowh = (long double)demo->win.w / (long double)demo->win.h;
    demo->cam.fovw = M_PI / 2.0f;
    demo->cam.near = 1.0L;
    demo->cam.proj = PROJ_TYPE_PERSPECTIVE;
}

static int init_mouse(demo_t *demo)
{
    demo->mouse.button_state = 0;
    demo->mouse.button_release = 0;
    demo->mouse.button_click = 0;
    for (size_t i = 0; i < 2; i++)
        demo_refresh_mouse_pos();
    demo_update_cursor_visibility(demo);
    for (size_t i = 0; i < 256; i++) {
        demo->input.key_state[i] = 0;
        demo->input.key_last[i] = 0;
        demo->input.key_press[i] = 0;
    }
    return (1);
}

static void init_win(demo_t *demo)
{
    demo->win.w = 1920;
    demo->win.h = 1080;
    demo->win.window = sfRenderWindow_create((sfVideoMode){demo->win.w,
    demo->win.h, 32}, "rtx on !", sfClose | sfFullscreen,
    &(sfContextSettings){24, 8, 2, 4, 3, 0, 1});
    if (demo->win.window == NULL)
        exit_full_custom();
    demo->win.frametime = sfClock_create();
    if (demo->win.frametime == NULL)
        exit_full_custom();
    demo->win.framelen = 1.0f / 60.0f;
    demo->win.fps_to_display = 60;
    demo->win.has_focus = 1;
    sfWindow_setVerticalSyncEnabled((sfWindow*)demo->win.window, sfTrue);
    if (!init_mouse(demo))
        exit_full_custom();
}

demo_t* demo_init(void)
{
    demo_t *res;

    res = malloc_safe(sizeof(demo_t));
    _demo = res;
    init_win(res);
    init_cam(res);
    init();
    clocks_init(res);
    _dungeons.cur_origin = (dvec3){0, 0, 0};
    tex_init(res);
    iu_init(res);
    player_init(res);
    gl_gen(res);
    shader_init(res);
    material_init(res);
    mesh_bank_init();
    world_init(res);
    world_load_map();
    demo_update_cursor_visibility(res);
    return (res);
}

void demo_quit(demo_t *demo)
{
    world_quit(demo);
    mesh_bank_quit();
    shader_quit(demo);
    gl_delete(demo);
    iu_quit();
    tex_quit(demo);
    texture2f_write(_lightmaps.base, _lightmaps.aperture);
    quit();
    sfRenderWindow_destroy(demo->win.window);
    sfClock_destroy(demo->win.frametime);
    clocks_quit(demo);
    free(demo);
}
