/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** headers
*/

#ifndef _MAT_STRUCT_H
#define _MAT_STRUCT_H

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
    vec3 vertex[3];
    vec3 normal;
    vec3 tangent;
    vec3 bitangent;
} rtx_triangle;

typedef struct {
    size_t count;
    size_t allocated;
    rtx_triangle *triangle;
} vec_rtx_triangle;

typedef struct {
    vec3 min;
    vec3 max;
    float size;
} bounds3;

typedef struct octree_s octree;
struct octree_s {
    octree *root;
    octree *sub[8];
    vec_rtx_triangle triangles;
    bounds3 bounds;
};

#endif
