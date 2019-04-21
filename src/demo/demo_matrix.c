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
        u = glGetUniformLocation(_demo->shader[i], "l_dir");
        glUniform3fv(u, 1, (void*)&l);
        u = glGetUniformLocation(_demo->shader[i], "p_cam");
        glUniform3fv(u, 1, (void*)&p);
    }
}

void shader_set(shader_t shader, dmat4 mvp, dmat4 world, dmat4 rot)
{
    mat4 mvp_actual;
    mat4 world_actual;
    mat4 rot_actual;
    gluint u;

    dmat4_mat4(mvp, mvp_actual);
    dmat4_mat4(world, world_actual);
    dmat4_mat4(rot, rot_actual);
    glUseProgram(_demo->shader[shader]);
    u = glGetUniformLocation(_demo->shader[shader], "mvp");
    glUniformMatrix4fv(u, 1, GL_FALSE, (void*)mvp_actual);
    u = glGetUniformLocation(_demo->shader[shader], "world");
    glUniformMatrix4fv(u, 1, GL_FALSE, (void*)world_actual);
    u = glGetUniformLocation(_demo->shader[shader], "rot");
    glUniformMatrix4fv(u, 1, GL_FALSE, (void*)rot_actual);
}

void refresh_vp(demo_t *demo)
{
    proj_t proj_struct = {0.3f, 4094.0f * 4, 90.0f, 16.0f / 9.0f};
    proj_t ortho_struct = proj_struct;

    ortho_struct.fov_w = 10.0f;
    if (demo->cam.proj == PROJ_TYPE_PERSPECTIVE)
        dmat4_perspective(proj_struct, demo->cam.mvp.proj);
    else
        dmat4_ortho(ortho_struct, demo->cam.mvp.proj);
    dmat4_rot(demo->cam.rot, demo->cam.mvp.rot);
    dmat4_view(demo->cam.pos, demo->cam.rot, demo->cam.mvp.view);
    dmat4_mul(demo->cam.mvp.proj, demo->cam.mvp.view, demo->cam.mvp.vp);
    send_uniform();
}
