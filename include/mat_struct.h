/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** headers
*/

#ifndef _MAT_STRUCT_H
#define _MAT_STRUCT_H

/* 1D ray */
typedef struct {
    float p;
    float v;
} ray1;

typedef struct {
    vec3 p;
    vec3 v;
} ray3;

typedef struct {
    ray3 ray;
    vec3 color;
    size_t count;
} ray3_color;

typedef struct {
    vec2 c;
    float r;
} circle;

typedef struct {
    float near_plane;
    float far_plane;
    float fov_w;
    float ratio_wh;
} proj_t;

typedef struct {
    vec2 p;
    vec2 s;
} rect_t;

#endif
