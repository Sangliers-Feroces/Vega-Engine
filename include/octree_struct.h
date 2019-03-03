/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** headers
*/

#ifndef _OCTREE_STRUCT_H
#define _OCTREE_STRUCT_H

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

struct octree_s {
    struct octree_s *root;    /* -> might be useful to reposition moving objects */
    struct octree_s *sub[8];
    vec_rtx_triangle triangles;
    bounds3 bounds;
};
typedef struct octree_s octree;

/* buffer for ray intersection (stores closest hit) */
typedef struct {
    rtx_triangle *triangle;
    vec3 p;
    vec3 bar;
    float min_t;
} inter_ray3;

typedef struct {
    size_t buf_size;
    size_t size;
    int32_t *data;
} gpu_serial_t;

#endif
