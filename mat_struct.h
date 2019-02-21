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
    texture2 *texture;
    vec2 uv[3];
    int is_linked;     /* set to one if the texture should be free'd with */
} texture2_binding;    /* the object linked                               */

/* type used for raytracing structure */
typedef struct {
    vec3 vertex[3];
    texture2_binding lightmap;
    texture2f *lumels;
    vec3 normal;               /* normal + tangent + bitangent         */
    vec3 tangent;              /* are very key to create tangent space */
    vec3 bitangent;            /* and then to make lights rays bounce  */
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
    vec3 bar;
    float min_t;
} inter_ray3;

#endif
