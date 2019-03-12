/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** demo_matrix
*/

#include "headers.h"

static void send_matrix(gluint program, mat4 vp)
{
    gluint matrix_id = glGetUniformLocation(program, "vp");

    glUniformMatrix4fv(matrix_id, 1, GL_FALSE, vp);
}

void set_matrix_vp(demo_t *demo, gluint program)
{
    vec3 pos = demo->cam.pos;
    vec3 rot = {0.0f, 0.0f, 0.0f};
    mat4 view; 
    mat4 proj;
    mat4 vp;
    proj_t proj_struct = {0.1f, 1000.0f, 90.0f, 16.0f/9.0f};

    mat4_perspective(proj_struct, proj);
    mat4_view(pos, rot, view);
    mat4_mul(proj, view, vp);
    send_matrix(program, vp);
}