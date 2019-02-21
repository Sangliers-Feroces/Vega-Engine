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

void demo_poll_input(demo_t *demo)
{
    for (size_t i = 0; i < KEY_COUNT; i++)
        demo->input.keystate[i] =
        sfKeyboard_isKeyPressed(demo->input.binding[i]);
    if (demo->input.keystate[KEY_UP])
        demo->cam.pos.y += CAM_MOVE;
    if (demo->input.keystate[KEY_DOWN])
        demo->cam.pos.y -= CAM_MOVE;
    if (demo->input.keystate[KEY_LEFT])
        demo->cam.pos.x -= CAM_MOVE;
    if (demo->input.keystate[KEY_RIGHT])
        demo->cam.pos.x += CAM_MOVE;
    if (sfKeyboard_isKeyPressed(sfKeyZ))
        demo->cam.pos.z += CAM_MOVE;
    if (sfKeyboard_isKeyPressed(sfKeyS))
        demo->cam.pos.z -= CAM_MOVE;
}
