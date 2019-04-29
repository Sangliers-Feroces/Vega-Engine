/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static void render_hdr_to_screen(void)
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDrawBuffers(1, (glenum[]){GL_COLOR_ATTACHMENT0});
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(_iu.data.vertex_array);
    glUseProgram(_demo->shader[SHADER_HDR].program);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _demo->buf.hdr_render_texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _demo->buf.dist_texture);
    glUniform1f(_demo->shader[SHADER_HDR].uniform[1], _demo->clocks.t);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void demo_loop(demo_t *demo)
{
    while (demo_poll_events(demo)) {
        demo_update_cursor_visibility(demo);
        demo->clocks.t = get_eleapsed_time_second(demo->clocks.game_clock);
        glBindFramebuffer(GL_FRAMEBUFFER, _demo->buf.hdr_framebuffer);
        glDrawBuffers(2, (glenum[]){GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1});
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        editor(demo);
        world_update();
        world_render();
        render_hdr_to_screen();
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
