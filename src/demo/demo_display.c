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

static void set_vertex_attrib(void)
{
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
        sizeof(vertext_array_t), BUFFER_OFFSET(0));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
        sizeof(vertext_array_t), BUFFER_OFFSET(offsetof(vertext_array_t, uv)));
}

static void display_loop(gluint vertex_buffer, gluint program_id,
size_t array_size, demo_t *demo)
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        send_aperture(demo, program_id);
        refresh_vp(demo, program_id);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        set_vertex_attrib();
        glBindTexture(GL_TEXTURE_2D, _lightmaps.base->id);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _lightmaps.base->id);
        glDrawArrays(GL_TRIANGLES, 0, array_size);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        sfRenderWindow_display(demo->win.window);
    } while (poll_events(demo));
}

void display_vertex_array(demo_t *demo, vertex_struct_t v_struct)
{
    gluint vertex_array_id;
    gluint vertex_buffer;
    gluint program_id;

    glGenVertexArrays(1, &vertex_array_id);
    glBindVertexArray(vertex_array_id);
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER,
    sizeof(vertext_array_t) * (v_struct.count * 3),
    v_struct.v_array, GL_STATIC_DRAW);
    program_id = shader_load_vert_frag(
    "src/gpu/shader/simplevertexshader.glsl",
    "src/gpu/shader/simplefragmentshader.glsl");
    glUseProgram(program_id);
    set_matrix_vp(demo, program_id);
    display_loop(vertex_buffer, program_id, v_struct.count * 3, demo);
}
