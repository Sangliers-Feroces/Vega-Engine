/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** demo_display
*/

#include "headers.h"

static void display_loop(gluint vertex_buffer, gluint program_id,
size_t array_size, demo_t *demo)
{
    do {
        glEnable(GL_DEPTH_TEST);
	    glDepthFunc(GL_LESS);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(program_id);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0);
        glDrawArrays(GL_TRIANGLES, 0, array_size);
        glDisableVertexAttribArray(0);
        sfRenderWindow_display(demo->win.window);
    } while (poll_events(demo));
}

void display_vertex_array(demo_t *demo, vertex_array_t v_struct)
{
    gluint vertex_array_id;
    gluint vertex_buffer;
    gluint program_id;

    glGenVertexArrays(1, &vertex_array_id);
    glBindVertexArray(vertex_array_id);
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * (v_struct.count * 3),
    v_struct.vertex_array, GL_STATIC_DRAW);
    program_id = shader_load_vert_frag("src/gpu/shader/simplevertexshader.glsl",
    "src/gpu/shader/simplefragmentshader.glsl");
    display_loop(vertex_buffer, program_id, v_struct.count * 3, demo);
}