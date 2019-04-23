/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

vec_rtx_triangle_ref vec_rtx_triangle_ref_create(size_t count)
{
    vec_rtx_triangle_ref res;

    res.count = count;
    res.triangle = (rtx_triangle**)malloc_safe(count * sizeof(rtx_triangle*));
    return res;
}

vec_rtx_triangle_ref vec_rtx_triangle_ref_get_void(void)
{
    vec_rtx_triangle_ref res;

    res.count = 0;
    res.triangle = NULL;
    return res;
}

void vec_rtx_triangle_ref_destroy(vec_rtx_triangle_ref vec)
{
    for (size_t i = 0; i < vec.count; i++)
        rtx_triangle_destroy(vec.triangle[vec.count - 1 - i]);
    free(vec.triangle);
}

transform_t transform_get_default(void)
{
    transform_t res;

    res.is_static = 1;
    res.pos = dvec3_init(0.0, 0.0, 0.0);
    res.scale = dvec3_init(1.0, 1.0, 1.0);
    res.rot = dvec3_init(0.0, 0.0, 0.0);
    dmat4_identity(res.model);
    dmat4_identity(res.model_rot);
    dmat4_identity(res.world);
    dmat4_identity(res.world_rot);
    return res;
}

col_ref_t col_ref_get_default(void)
{
    col_ref_t res;

    res.mesh = mesh_full_ref_get_null();
    res.ref = vec_rtx_triangle_ref_get_void();
    res.is_on = 0;
    return res;
}

render_obj_t render_obj_get_default(void)
{
    render_obj_t res;

    res.mesh = mesh_full_ref_get_null();
    res.material = MATERIAL_MAX;
    return res;
}

void render_obj_destroy(render_obj_t render)
{
    if (render.mesh.ref_type != MESH_FULL_REF_STANDALONE)
        return;
    if (render.mesh.m == NULL)
        return;
    mesh_full_destroy(render.mesh.m);
}

vec_entity3_t vec_entity3_create(void)
{
    vec_entity3_t res;

    res.count = 0;
    res.allocated = 0;
    res.ent = NULL;
    return res;
}

size_t vec_entity3_add(vec_entity3_t *vec, entity3 *entity)
{
    size_t cur = vec->count++;
    entity3 **new_ent;

    if (vec->count > vec->allocated) {
        vec->allocated += 16;
        new_ent = (entity3**)malloc_safe(vec->allocated * sizeof(entity3*));
        for (size_t i = 0; i < cur; i++)
            new_ent[i] = vec->ent[i];
        free(vec->ent);
        vec->ent = new_ent;
    }
    vec->ent[cur] = entity;
    return cur;
}

void vec_entity3_destroy(vec_entity3_t vec)
{
    for (size_t i = 0; i < vec.count; i++)
        entity3_destroy(vec.ent[i]);
    free(vec.ent);
}

entity3* entity3_create_pos(entity3 *parent, dvec3 pos)
{
    entity3 *res = (entity3*)malloc_safe(sizeof(entity3));

    res->trans = transform_get_default();
    res->trans.pos = pos;
    entity3_trans_update_model(res);
    res->col = col_ref_get_default();
    for (size_t i = 0; i < WORLD_LOD_COUNT; i++)
        res->render[i] = render_obj_get_default();
    res->root = parent;
    res->root_ndx = ~0ULL;
    res->sub = vec_entity3_create();
    if (parent != NULL) {
        res->root_ndx = vec_entity3_add(&parent->sub, res);
        entity3_update_solo(res, parent->trans.world, parent->trans.world_rot);
    }
    res->tag = ENTITY3_TAG_NONE;
    return res;
}

entity3* entity3_create(entity3 *parent)
{
    return entity3_create_pos(parent, dvec3_init(0.0, 0.0, 0.0));
}

void entity3_set_col(entity3 *ent, int is_on)
{
    dvec3 p[3];

    if (!is_on) {
        if (!ent->col.is_on)
            return;
        ent->col.is_on = is_on;
        vec_rtx_triangle_ref_destroy(ent->col.ref);
        return;
    }
    if ((ent->col.is_on) || (ent->col.mesh.m == NULL))
        return;
    ent->col.is_on = is_on;
    ent->col.ref =
    vec_rtx_triangle_ref_create(ent->col.mesh.m->mesh->vertex_count / 3);
    for (size_t i = 0; i < ent->col.mesh.m->mesh->vertex_count / 3; i++) {
        for (size_t j = 0; j < 3; j++)
            p[j] = dmat4_mul_vec3(ent->trans.world,
            ent->col.mesh.m->mesh->vertex[i * 3 + j].pos);
        ent->col.ref.triangle[i] =
        octree_insert_triangle(&_demo->world.tree, rtx_triangle_create(p));
    }
}

void entity3_destroy(entity3 *entity)
{
    while (entity->sub.count > 0)
        entity3_destroy(entity->sub.ent[0]);
    vec_entity3_destroy(entity->sub);
    entity3_set_col(entity, 0);
    for (size_t i = 0; i < WORLD_LOD_COUNT; i++)
        render_obj_destroy(entity->render[i]);
    if (entity->root != NULL) {
        entity->root->sub.ent[entity->root_ndx] =
        entity->root->sub.ent[-- entity->root->sub.count];
        entity->root->sub.ent[entity->root_ndx]->root_ndx = entity->root_ndx;
    }
    free(entity);
}

entity3* chunk_add_entity(chunk_t *chunk)
{
    entity3 *res = entity3_create(chunk->ents);

    return res;
}

void entity3_bind_col(entity3 *entity, mesh_full_ref_t collision_mesh)
{
    if (collision_mesh.m == NULL) {
        printf("Warning: set null collisions.\n");
        return;
    }
    if (entity->col.mesh.m != NULL)
        entity3_set_col(entity, 0);
    entity->col.mesh = collision_mesh;
    entity3_set_col(entity, 1);
}

void entity3_set_render(entity3 *ent, size_t lod, mesh_full_ref_t mesh,
material_t material)
{
    if (!(lod < (size_t)WORLD_LOD_COUNT)) {
        printf("Error: oob lod (got %zu).\n", lod);
        exit(84);
    }
    ent->render[lod].mesh = mesh;
    ent->render[lod].material = material;
}

mesh_full_t* entity3_create_render(entity3 *ent, size_t lod,
material_t material, int has_ext)
{
    mesh_full_t *mesh;

    if (!(lod < (size_t)WORLD_LOD_COUNT)) {
        printf("Error: oob lod (got %zu).\n", lod);
        exit(84);
    }
    if ((ent->render[lod].mesh.m != NULL) &&
    (ent->render[lod].mesh.ref_type == MESH_FULL_REF_STANDALONE))
        printf("Warning: overwriting standalone rendering geometry.\n");
    render_obj_destroy(ent->render[lod]);
    mesh = mesh_full_create(1, has_ext);
    ent->render[lod].mesh = mesh_full_ref_init(MESH_FULL_REF_STANDALONE, mesh);
    ent->render[lod].material = material;
    return mesh;
}
