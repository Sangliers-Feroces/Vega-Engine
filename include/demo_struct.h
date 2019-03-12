/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#ifndef _DEMO_STRUCT_H
#define _DEMO_STRUCT_H

#include "headers.h"

typedef enum {
    KEY_UP = 0,
    KEY_DOWN = 1,
    KEY_LEFT = 2,
    KEY_RIGHT = 3,
    KEY_JUMP = 4,
    KEY_ATK = 5,
    KEY_COUNT = 6
} key_act_t;

typedef struct {
    sfKeyCode binding[KEY_COUNT];
    char keystate[KEY_COUNT];
} input_t;

typedef struct {
    uint32_t w;
    uint32_t h;
    sfRenderWindow *window;
} win_t;

typedef struct {
    vec3 pos;
    vec3 rot;
    long double fovw;
    long double ratiowh;
    long double near;
    float aperture;
} cam_t;

typedef struct {
    int first_click;
    sfVector2i mouse_pos;
} mouse_t;

typedef struct {
    win_t win;
    cam_t cam;
    input_t input;
    octree *tree;
    mouse_t mouse;
    mvp_t mvp;
} demo_t;

#endif
