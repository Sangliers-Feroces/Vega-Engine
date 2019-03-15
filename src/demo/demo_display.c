/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** demo_display
*/

#include "headers.h"

void send_aperture(demo_t *demo, gluint program)
{
    glint aperture = glGetUniformLocation(program, "aperture");

    glUniform1f(aperture, demo->cam.aperture);
}

static void set_vertex_attrib(demo_t *demo)
{
    refresh_vertex_buffer(demo);
    glBindBuffer(GL_ARRAY_BUFFER, demo->buf.vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER,
    sizeof(vertext_array_t) * (demo->buf.vertex_struct.count * 3),
    demo->buf.vertex_struct.v_array, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
    sizeof(vertext_array_t), BUFFER_OFFSET(0));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
    sizeof(vertext_array_t), BUFFER_OFFSET(offsetof(vertext_array_t, uv)));
}

static void draw_geom(size_t size, int do_backwire)
{
    glFrontFace(GL_CW);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLES, 0, size);
    if (do_backwire) {
        glFrontFace(GL_CCW);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_TRIANGLES, 0, size);
    }
    glFrontFace(GL_CW);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void demo_loop(demo_t *demo)
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(demo->buf.lightmap_shader);
        send_aperture(demo, demo->buf.lightmap_shader);
        refresh_vp(demo, demo->buf.lightmap_shader);
        set_vertex_attrib(demo);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _lightmaps.base->id);
        draw_geom(demo->buf.vertex_struct.count * 3,
        demo->player.state == GAME_EDITOR);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        ui_swicth_button_action(demo);
        ui_display(1, demo);
        sfRenderWindow_display(demo->win.window);
    } while (poll_events(demo));
}
