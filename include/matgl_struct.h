/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** headers
*/

#ifndef _MATGL_STRUCT_H
#define _MATGL_STRUCT_H

/* GL types */
typedef struct {
    float x;
    float y;
} vec2;

typedef struct {
    float x;
    float y;
    float z;
} vec3;

typedef struct {
    float x;
    float y;
    float z;
    float w;
} vec4;

typedef struct {
    int32_t x;
    int32_t y;
} ivec2;

typedef struct {
    ssize_t x;
    ssize_t y;
} ssize2;

typedef struct {
    ssize2 p;
    ssize2 s;
} srect;

typedef float mat4[4][4];

typedef struct {
    size_t w;
    size_t h;
    vec3 *vec3;
} arr2d_vec3_t;

typedef struct {
    size_t count;
    vec3 *vec3;
} arr_vec3_t;

#endif
