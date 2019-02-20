/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** headers
*/

#ifndef _MAT_STRUCT_H
#define _MAT_STRUCT_H

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

/* 1D ray */
typedef struct {
    float p;
    float v;
} ray1;

typedef struct {
    vec3 p;
    vec3 v;
} ray3;

/* type used for raytracing structure */
typedef struct {
    vec3 vertex[3];
    vec3 normal;        /* normal + tangent + bitangent         */
    vec3 tangent;       /* are very key to create tangent space */
    vec3 bitangent;     /* and then to make lights rays bounce  */
} rtx_triangle;

/* another std::vector */
typedef struct {
    size_t count;
    size_t allocated;
    rtx_triangle *triangle;
} vec_rtx_triangle;

/* used to define an octree node space */
typedef struct {
    vec3 min;       /* these two vectors actually describe */
    vec3 max;       /* a cube in 3D space                  */
    float size;     /* -> cube size */
} bounds3;

typedef struct octree_s octree;
struct octree_s {
    octree *root;    /* -> might be useful to reposition moving objects */
    octree *sub[8];
    vec_rtx_triangle triangles;
    bounds3 bounds;
};

/* buffer for ray intersection (stores closest hit) */
typedef struct {
    rtx_triangle *triangle;
    vec3 p;
    float min_t;
} inter_ray3;

#endif
