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

    if (!demo->mouse.first_click)
        return;
    new_pos = sfMouse_getPositionRenderWindow(demo->win.window);
    demo->cam.rot.y += (float)(new_pos.x - demo->mouse.mouse_pos.x) * 0.002f;
    demo->cam.rot.x += (float)(new_pos.y - demo->mouse.mouse_pos.y) * 0.002f;
    /*if (new_pos.x - demo->mouse.mouse_pos.x > 0)
        demo->cam.rot.y += 0.0174533f;
    else if (new_pos.x - demo->mouse.mouse_pos.x < 0)
        demo->cam.rot.y -= 0.0174533f;
    if (new_pos.y - demo->mouse.mouse_pos.y > 0)
        demo->cam.rot.x += 0.0174533f;
    else if (new_pos.y - demo->mouse.mouse_pos.y < 0)
        demo->cam.rot.x -= 0.0174533f;*/
    demo->mouse.mouse_pos = new_pos;
}

static void send_matrix(gluint program, mat4 vp)
{
    gluint matrix_id = glGetUniformLocation(program, "vp");

    glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &vp[0][0]);
}

void refresh_vp(demo_t *demo, gluint program)
{
    mat4_view(demo->cam.pos, demo->cam.rot, demo->mvp.view);
    mat4_mul(demo->mvp.proj, demo->mvp.view, demo->mvp.vp);
    send_matrix(program, demo->mvp.vp);
}

void set_matrix_vp(demo_t *demo, gluint program)
{
    vec3 pos = {0.0f, 0.0f, -5.0f};
    vec3 rot = {0.0f, 0.0f, 0.0f};
    proj_t proj_struct = {0.1f, 1000.0f, 90.0f, 16.0f/9.0f};

    mat4_perspective(proj_struct, demo->mvp.proj);
    mat4_view(pos, rot, demo->mvp.view);
    mat4_mul(demo->mvp.proj, demo->mvp.view, demo->mvp.vp);
    send_matrix(program, demo->mvp.vp);
}
