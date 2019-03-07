/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#ifndef _DEMO_STRUCT_H
#define _DEMO_STRUCT_H

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
    uint32_t *data;
    sfTexture *_texture;
    sfSprite *_sprite;
} win_t;

typedef struct {
    vec3 pos;
    vec3 rot;
    long double fovw;
    long double ratiowh;
    long double near;
} cam_t;

typedef struct {
    win_t win;
    cam_t cam;
    input_t input;
    octree *tree;
} demo_t;

#endif