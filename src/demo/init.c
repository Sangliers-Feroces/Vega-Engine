/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** various loaders : valid within a gl context
*/

#include "headers.h"

void init(void)
{
    thread_init();
    srand(time(NULL));
    load_gl_fun();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
    lightmap_init();
}

void quit(void)
{
    thread_quit();
    lightmap_quit();
}

void gl_gen(demo_t *demo)
{
    demo->buf.vertex_struct = (vertex_struct_t){0, 0, NULL};
    glGenVertexArrays(1, &demo->buf.vertex_array_id);
    glBindVertexArray(demo->buf.vertex_array_id);
    glGenBuffers(1, &demo->buf.vertex_buffer);
    demo->buf.lightmap_shader = shader_load_vert_frag(
    "src/gpu/shader/lightmap_vertex.glsl",
    "src/gpu/shader/lightmap_fragment.glsl");
    if (demo->buf.lightmap_shader == 0) {
        printf("Can't open lightmap shader.\n");
        exit(84);
    }
}

void gl_delete(demo_t *demo)
{
    glDeleteBuffers(1, &demo->buf.vertex_buffer);
    glDeleteProgram(demo->buf.lightmap_shader);
    glDeleteVertexArrays(1, &demo->buf.vertex_array_id);
    free(demo->buf.vertex_struct.v_array);
}
