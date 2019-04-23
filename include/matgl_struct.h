/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** headers
*/

#pragma once

/* GL types */
typedef struct {
    float x;
    float y;
} vec2;

typedef struct {
    double x;
    double y;
} dvec2;

typedef struct {
    float x;
    float y;
    float z;
} vec3;

typedef struct {
    double x;
    double y;
    double z;
} dvec3;

typedef struct {
    float x;
    float y;
    float z;
    float w;
} vec4;

typedef struct {
    double x;
    double y;
    double z;
    double w;
} dvec4;

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
typedef double dmat4[4][4];

typedef struct {
    dmat4 data;
} dmat4_w;

typedef struct {
    size_t w;
    size_t h;
    dvec3 *dvec3;
} arr2d_dvec3_t;

typedef struct {
    size_t count;
    dvec3 *dvec3;
} arr_dvec3_t;
