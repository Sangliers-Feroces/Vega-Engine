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
    glFrontFace(GL_CW);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_MULTISAMPLE);
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
    demo->buf.world_shader = shader_load_vert_frag(
    "src/gpu/shader/world_vertex.glsl",
    "src/gpu/shader/world_fragment.glsl");
    if ((demo->buf.lightmap_shader == 0) || (demo->buf.world_shader == 0)) {
        printf("Can't open lightmap shader.\n");
        exit(84);
    }
    glGenVertexArrays(1, &demo->buf.world_vertex_array);
    demo->buf.to_draw = vec_render_call_init();
    glGenFramebuffers(1, &_demo->buf.hdr_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _demo->buf.hdr_framebuffer);
    glGenTextures(1, &_demo->buf.hdr_render_texture);
    glBindTexture(GL_TEXTURE_2D, _demo->buf.hdr_render_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, _demo->win.w, _demo->win.h, 0,
    GL_RGBA, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glGenRenderbuffers(1, &_demo->buf.hdr_depthbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _demo->buf.hdr_depthbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT,
    _demo->win.w, _demo->win.h);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
    GL_RENDERBUFFER, _demo->buf.hdr_depthbuffer);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
    _demo->buf.hdr_render_texture, 0);
    glGenTextures(1, &_demo->buf.dist_texture);
    glBindTexture(GL_TEXTURE_2D, _demo->buf.dist_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, _demo->win.w, _demo->win.h, 0,
    GL_RED, GL_FLOAT, 0);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1,
    _demo->buf.dist_texture, 0);
    glDrawBuffers(2, (glenum[]){GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1});
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void gl_delete(demo_t *demo)
{
    glDeleteBuffers(1, &demo->buf.vertex_buffer);
    glDeleteProgram(demo->buf.lightmap_shader);
    glDeleteProgram(demo->buf.world_shader);
    glDeleteVertexArrays(1, &demo->buf.vertex_array_id);
    glDeleteVertexArrays(1, &demo->buf.world_vertex_array);
    free(demo->buf.vertex_struct.v_array);
    vec_render_call_destroy(demo->buf.to_draw);
}
