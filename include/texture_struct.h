/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** headers
*/

#ifndef _TEXTURE_STRUCT_H
#define _TEXTURE_STRUCT_H

typedef struct {
    uint32_t w;
    uint32_t h;
    size_t max_ndx;
    uint32_t *pixel;
    float *lumel;
} texture2;

typedef struct {
    uint32_t w;
    uint32_t h;
    size_t max_ndx;
    vec3 *pixel;
} texture2f;

#endif
