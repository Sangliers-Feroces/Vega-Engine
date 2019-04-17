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
    dvec3 vertex[3];
    texture2f_binding lightmap;
    texture2_binding albelo;
    dvec3 normal;               /* normal + tangent + bitangent         */
    dvec3 tangent;              /* are very key to create tangent space */
    dvec3 bitangent;            /* and then to make lights rays bounce  */
    int data;
} rtx_triangle;

/* another std::vector */
typedef struct {
    size_t count;
    size_t allocated;
    rtx_triangle **triangle;
} vec_rtx_triangle;

/* used to define an octree node space */
typedef struct {
    dvec3 min;       /* these two vectors actually describe */
    dvec3 max;       /* a cube in 3D space                  */
    double size;     /* -> cube size */
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
    dvec3 p;
    dvec3 bar;
    double min_t;
} inter_ray3;

typedef struct {
    size_t buf_size;
    size_t size;
    int32_t *data;
} gpu_serial_t;

typedef struct {
    dvec3 point;
    vec2 uv;
    vec2 uv_albedo;
} vertext_array_t;

typedef struct {
    size_t count;
    size_t offset;
    vertext_array_t *v_array;
} vertex_struct_t;

typedef struct {
    vec3 pos;
    vec2 uv;
} vertex_serial_t;

typedef struct {
    vec3 pos;
    vec3 normal;
    vec2 uv;
} vertex_t;

typedef struct {
    size_t vertex_count;
    vertex_t *vertex;
    gluint buffer;
    texture2 *texture;
} model_t;

typedef struct {
    dvec3 pos;
    dvec3 scale;
    dvec3 rot;
    mat4 trans;
    mat4 rot_mat;
    model_t *model;
    vertex_t *vertex;
} entity_t;

typedef struct {
    vertex_t *vertex;
    dvec3 p;
    dvec3 bar;
    double min_t;
} inter_ray3_ent;

typedef struct {
    dvec3 *vertex;
    dvec3 mid;
} terrain_search_t;

#endif
