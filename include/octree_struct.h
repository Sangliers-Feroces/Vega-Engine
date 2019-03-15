/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** headers
*/

#ifndef _OCTREE_STRUCT_H
#define _OCTREE_STRUCT_H

/* type used for raytracing structure */
typedef struct {
    vec3 vertex[3];
    texture2f_binding lightmap;
    texture2_binding albelo;
    vec3 normal;               /* normal + tangent + bitangent         */
    vec3 tangent;              /* are very key to create tangent space */
    vec3 bitangent;            /* and then to make lights rays bounce  */
} rtx_triangle;

/* another std::vector */
typedef struct {
    size_t count;
    size_t allocated;
    rtx_triangle **triangle;
} vec_rtx_triangle;

/* used to define an octree node space */
typedef struct {
    vec3 min;       /* these two vectors actually describe */
    vec3 max;       /* a cube in 3D space                  */
    float size;     /* -> cube size */
} bounds3;

struct octree_s {
    struct octree_s *root;    /* -> might be useful to reposition */
    struct octree_s *sub[8];  /* moving objects                   */
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

typedef struct {
    vec3 point;
    vec2 uv;
} vertext_array_t;

typedef struct {
    size_t count;
    size_t offset;
    vertext_array_t *v_array;
} vertex_struct_t;

#endif
