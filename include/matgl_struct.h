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

typedef float mat4[4][4];

#endif
