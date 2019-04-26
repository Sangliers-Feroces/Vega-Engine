/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

void demo_loop(demo_t *demo)
{
    while (demo_poll_events(demo)) {
        demo_update_cursor_visibility(demo);
        demo->game_time = get_eleapsed_time_second(demo->clocks.game_clock);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        editor(demo);
        world_update();
        world_render();
        iu_display();
        sfRenderWindow_display(demo->win.window);
    }
}

int demo(arg_t args)
{
    demo_t *demo = demo_init();

    (void)args;
    if (!start(demo)) {
        demo_quit(demo);
        return 0;
    }
    demo_loop(demo);
    demo_quit(demo);
    return (0);
}
