/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

void demo_init_input(demo_t *demo)
{
    demo->input.binding[KEY_UP] = sfKeyUp;
    demo->input.binding[KEY_DOWN] = sfKeyDown;
    demo->input.binding[KEY_LEFT] = sfKeyLeft;
    demo->input.binding[KEY_RIGHT] = sfKeyRight;
    demo->input.binding[KEY_JUMP] = sfKeyX;
    demo->input.binding[KEY_ATK] = sfKeyW;
}

static void get_cam_x_z(demo_t *demo, vec3 *x, vec3 *z)
{
    mat4 rot;
    vec4 res;

    mat4_rot(demo->cam.rot, rot);
    res = mat4_mul_vec(rot, (vec4){0.0, 0.0, 1.0, 1.0});
    *z = (vec3){res.x, res.y, res.z};
    res = mat4_mul_vec(rot, (vec4){1.0, 0.0, 0.0, 1.0});
    *x = (vec3){res.x, res.y, res.z};
    return ;
}

void demo_poll_input(demo_t *demo)
{
    vec3 cam_x;
    vec3 cam_z;

    get_cam_x_z(demo, &cam_x, &cam_z);
    for (size_t i = 0; i < KEY_COUNT; i++)
        demo->input.keystate[i] =
        sfKeyboard_isKeyPressed(demo->input.binding[i]);
    if (sfKeyboard_isKeyPressed(sfKeyZ))
        demo->cam.pos =
        vec3_add(demo->cam.pos, vec3_muls(cam_z, CAM_MOVE));
    if (sfKeyboard_isKeyPressed(sfKeyS))
        demo->cam.pos =
        vec3_sub(demo->cam.pos, vec3_muls(cam_z, CAM_MOVE));
    if (sfKeyboard_isKeyPressed(sfKeyD))
        demo->cam.pos =
        vec3_add(demo->cam.pos, vec3_muls(cam_x, CAM_MOVE));
    if (sfKeyboard_isKeyPressed(sfKeyQ))
        demo->cam.pos =
        vec3_sub(demo->cam.pos, vec3_muls(cam_x, CAM_MOVE));
}
