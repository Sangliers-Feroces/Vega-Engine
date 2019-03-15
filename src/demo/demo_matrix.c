/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** demo_matrix
*/

#include "headers.h"

void check_mouse_move(demo_t *demo)
{
    sfVector2i new_pos;
    float sensi = 0.0015f;

    if (!(demo->mouse.button_state & sfMouseRight))
        return;
    new_pos = sfMouse_getPositionRenderWindow(demo->win.window);
    demo->cam.rot.y -= (float)(new_pos.x - demo->mouse.mouse_pos.x) * sensi;
    demo->cam.rot.x -= (float)(new_pos.y - demo->mouse.mouse_pos.y) * sensi;
    demo->mouse.mouse_pos = new_pos;
}

static void send_matrix(gluint program, mat4 vp)
{
    gluint matrix_id = glGetUniformLocation(program, "vp");

    glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &vp[0][0]);
}

void refresh_vp(demo_t *demo, gluint program)
{
    proj_t proj_struct = {0.1f, 1000.0f, 90.0f, 16.0f / 9.0f};
    proj_t ortho_struct = proj_struct;

    ortho_struct.fov_w = 10.0f;
    if (demo->cam.proj == PROJ_TYPE_PERSPECTIVE)
        mat4_perspective(proj_struct, demo->cam.mvp.proj);
    else
        mat4_ortho(ortho_struct, demo->cam.mvp.proj);
    mat4_view(demo->cam.pos, demo->cam.rot, demo->cam.mvp.view);
    mat4_mul(demo->cam.mvp.proj, demo->cam.mvp.view, demo->cam.mvp.vp);
    send_matrix(program, demo->cam.mvp.vp);
}
