/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** demo_matrix
*/

#include "headers.h"

static void send_uniform(void)
{
    gluint u;
    vec3 l = dvec3_vec3(dvec3_muls(_demo->buf.l, -1.0));
    vec3 p = dvec3_vec3(_demo->cam.pos);

    for (size_t i = 0; i < SHADER_MAX; i++) {
        glUseProgram(_demo->shader[i]);
        u = glGetUniformLocation(_demo->shader[i], "vp");
        glUniformMatrix4fv(u, 1, GL_FALSE, (void*)_demo->cam.mvp.vp);
        u = glGetUniformLocation(_demo->shader[i], "l_dir");
        glUniform3fv(u, 1, (void*)&l);
        u = glGetUniformLocation(_demo->shader[i], "p_cam");
        glUniform3fv(u, 1, (void*)&p);
    }
}

void refresh_vp(demo_t *demo)
{
    proj_t proj_struct = {0.3f, 4094.0f * 4, 90.0f, 16.0f / 9.0f};
    proj_t ortho_struct = proj_struct;

    ortho_struct.fov_w = 10.0f;
    if (demo->cam.proj == PROJ_TYPE_PERSPECTIVE)
        mat4_perspective(proj_struct, demo->cam.mvp.proj);
    else
        mat4_ortho(ortho_struct, demo->cam.mvp.proj);
    mat4_rot(demo->cam.rot, demo->cam.mvp.rot);
    mat4_view(demo->cam.pos, demo->cam.rot, demo->cam.mvp.view);
    mat4_mul(demo->cam.mvp.proj, demo->cam.mvp.view, demo->cam.mvp.vp);
    send_uniform();
}
