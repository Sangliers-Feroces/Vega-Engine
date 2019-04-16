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
    double p;
    double v;
} ray1;

typedef struct {
    dvec3 p;
    dvec3 v;
} ray3;

typedef struct {
    ray3 ray;
    dvec3 color;
    size_t count;
} ray3_color;

typedef struct {
    vec2 c;
    float r;
} circle;

typedef enum {
    PROJ_TYPE_PERSPECTIVE,
    PROJ_TYPE_ORTHOGRAPHIC
} proj_type_t;

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

typedef struct {
    mat4 model;
    mat4 view;
    mat4 proj;
    mat4 vp;
} mvp_t;

typedef struct {
    dvec3 tl;
    dvec3 tr;
    dvec3 bl;
    dvec3 br;
} ray_viewport_t;

#endif
