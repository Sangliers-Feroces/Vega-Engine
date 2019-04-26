/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#pragma once

#define WORLD_LOD_COUNT 3
#define WORLD_LOD_MAX (WORLD_LOD_COUNT - 1)
#define CHUNK_SIZE_TERRAIN 1024.0
#define CHUNK_SIZE 256.0
#define CHUNK_TERRAIN_SUB_SIZE ((ssize_t)(CHUNK_SIZE_TERRAIN / CHUNK_SIZE))
#define CHUNK_GEN_ITER 6
#define CHUNK_GEN_EXT_ITER 2
#define CHUNK_LOAD_DISTANCE 8

typedef struct {
    size_t lod;
    vec_rtx_triangle *geom;
    size_t vertex_count;
    gluint vertex_buffer;
    gluint vertex_array;
    int do_reupload_buf;
} chunk_lod_t;

typedef struct {
    arr_dvec3_t data[2][2][CHUNK_GEN_ITER];  // x, then z, negative, positive
} chunk_border_t;

typedef struct {
    int is_static;
    int is_physics;
    int is_grounded;
    dvec3 pos;
    dvec3 scale;
    dvec3 rot;
    dvec3 speed;
    dmat4 model;
    dmat4 model_rot;
    dmat4 world;
    dmat4 world_rot;
} transform_t;

typedef struct {
    int do_upload;
    int do_reupload;
    gluint vertex_buffer;
    gluint vertex_array;
} mesh_gpu_t;

typedef struct {
    size_t vertex_count;
    size_t vertex_allocated;
    vertex_t *vertex;
    mesh_gpu_t gpu;
} mesh_t;

typedef struct {
    vec2 uv_ext;
    float tex_a;
    float tex_b;
    float ratio;
} vertex_ext_t;

typedef struct {
    mesh_t *mesh;
    int has_ext;
    size_t ext_count;
    size_t ext_allocated;
    vertex_ext_t *ext;
    mesh_gpu_t gpu;
} mesh_full_t;

typedef enum {
    MESH_FULL_REF_RENDER_LOD0,
    MESH_FULL_REF_RENDER_LOD1,
    MESH_FULL_REF_RENDER_LOD2,
    MESH_FULL_REF_STANDALONE,
    MESH_FULL_REF_BANK
} mesh_full_ref_type_t;

typedef struct {
    mesh_full_ref_type_t ref_type;
    mesh_full_t *m;
} mesh_full_ref_t;

typedef struct {
    size_t count;
    size_t allocated;
    mesh_full_t **mesh;
} vec_mesh_full_t;

typedef struct {
    mesh_full_ref_t mesh;
    vec_rtx_triangle_ref ref;
    int is_on;
} col_ref_t;

typedef struct {
    mesh_full_ref_t mesh;
    material_t material;
} render_obj_t;

typedef struct entity3 entity3;

typedef struct {
    size_t count;
    size_t allocated;
    entity3 **ent;
} vec_entity3_t;

typedef void (*trigger_on_hit_fun_t)(entity3 *ent, entity3 *other);

typedef struct {
    dvec3 size;
    trigger_on_hit_fun_t on_hit;
    size_t ndx;
} trigger_t;

typedef enum {
    TRIGGER_ON_HIT_NONE,
    TRIGGER_ON_HIT_MAX
} trigger_on_hit_t;

typedef struct {
    trigger_on_hit_t trigger;
    trigger_on_hit_fun_t on_hit;
} trigger_on_hit_desc_t;

typedef struct {
    size_t count;
    size_t allocated;
    trigger_t **trigger;
} vec_trigger_t;

typedef enum  {
    ENTITY3_TAG_NONE,
    ENTITY3_TAG_TERRAIN,
    ENTITY3_TAG_PLAYER,
    ENTITY3_TAG_CAMERA,
    ENTITY3_TAG_MAX
} entity3_tag_t;

struct entity3 {
    transform_t trans;
    render_obj_t render[WORLD_LOD_COUNT];
    col_ref_t col;
    trigger_t *trigger;
    entity3_tag_t tag;
    entity3 *root;
    size_t root_ndx;
    vec_entity3_t sub;
};

typedef struct {
    ssize2 pos;
    chunk_border_t border;
    chunk_border_t border_ter;
    arr2d_dvec3_t terrain_base;
    size_t world_ndx;
    entity3 *ents;
    entity3 *ents_global;   // used on unloaded chunks for far entities
    entity3 *terrain;
    entity3 *inserting;
    int is_stalled;
} chunk_t;

typedef struct {
    entity3_tag_t tag;
    void (*fun)(entity3 *ent);
} entity3_tag_update_desc_t;

typedef struct {
    char *map_path;
    size_t chunk_count;
    size_t chunk_allocated;
    chunk_t **chunk;        // used for rendering / world intersection
    entity3 *ents;
    entity3 *ents_global;   // used on unloaded chunks for far entities
    entity3 *player;
    entity3 *camera;
    dvec3 light_dir;
    vec_trigger_t triggers; // loaded triggers
    srect chunk2d_area;
    chunk_t **chunk2d;      // 2d array for fast lookup
    octree *tree;           // collision data is exclusively stored here
    void (*tag_update[ENTITY3_TAG_MAX])(entity3 *ent);
    trigger_on_hit_fun_t trigger_on_hit[TRIGGER_ON_HIT_MAX];
} world_t;

typedef struct {
    vec3 pos;
    vec3 normal;
    vec2 uv_albedo;
    vec2 uv_lightmap;
} chunk_vertex_t;

typedef struct {
    size_t count;
    chunk_vertex_t *vertex;
} vec_chunk_vertex_t;

typedef struct {
    dvec3 pos;
    dvec3 normal;
    vec2 uv_albedo;
    vec2 uv_lightmap;
} chunk_dvertex_t;

typedef struct {
    size_t count;
    chunk_dvertex_t *dvertex;
} vec_chunk_dvertex_t;
