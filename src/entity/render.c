/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static void mesh_full_refresh(mesh_full_t *mesh)
{
    if (mesh->has_ext) {
        if (mesh->gpu.do_reupload) {
            glBindBuffer(GL_ARRAY_BUFFER, mesh->gpu.vertex_buffer);
            glBufferData(GL_ARRAY_BUFFER,
            mesh->ext_count * sizeof(vertex_ext_t), mesh->ext, GL_STATIC_DRAW);
            mesh->gpu.do_reupload = 0;
        }
    }
    if (mesh->mesh->gpu.do_reupload) {
        glBindBuffer(GL_ARRAY_BUFFER, mesh->mesh->gpu.vertex_buffer);
        glBufferData(GL_ARRAY_BUFFER,
        mesh->mesh->vertex_count * sizeof(vertex_t),
        mesh->mesh->vertex, GL_STATIC_DRAW);
        mesh->mesh->gpu.do_reupload = 0;
    }
}

static void render_obj_draw(render_obj_t render, dmat4 mvp, dmat4 world,
dmat4 rot)
{
    mesh_full_refresh(render.mesh.m);
    if (render.mesh.m->has_ext) {
        if (_demo->material[render.material].is_transparent)
            return render_delay_call((render_call_t){render.material,
            dmat4_dmat4_w(mvp), dmat4_dmat4_w(world), dmat4_dmat4_w(rot),
            render.mesh.m->gpu.vertex_array, render.mesh.m->ext_count});
        _demo->material[render.material].world(mvp, world, rot);
        glBindVertexArray(render.mesh.m->gpu.vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, render.mesh.m->ext_count);
    } else {
        if (_demo->material[render.material].is_transparent)
            return render_delay_call((render_call_t){render.material,
            dmat4_dmat4_w(mvp), dmat4_dmat4_w(world), dmat4_dmat4_w(rot),
            render.mesh.m->mesh->gpu.vertex_array,
            render.mesh.m->mesh->vertex_count});
        _demo->material[render.material].entity(mvp, world, rot);
        glBindVertexArray(render.mesh.m->mesh->gpu.vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, render.mesh.m->mesh->vertex_count);
    }
}

static size_t get_max_lod(render_obj_lod_dist_t lod, double dist)
{
    float dist2[RENDER_OBJ_LOD_DIST_MAX] = {384.0, 64.0, CHUNK_SIZE * 1.7,
    CHUNK_SIZE * 1.7 / 8.0};
    float dist1[RENDER_OBJ_LOD_DIST_MAX] = {768.0, 128.0, CHUNK_SIZE * 1.7,
    CHUNK_SIZE * 1.7 / 8.0};

    if (dist < (dist2[lod] * dist2[lod]))
        return 2;
    else if (dist < (dist1[lod] * dist1[lod]))
        return 1;
    else
        return 0;
}

static double get_ent_dist(entity3 *ent)
{
    dvec3 p = dmat4_trans(ent->trans.world);
    dvec3 c = dmat4_trans(_demo->world.camera->trans.world);

    return dvec3_dist_sq((dvec3){p.x, 0.0, p.z},
    (dvec3){c.x, 0.0, c.z});
}

void entity3_render(entity3 *ent, dmat4 vp)
{
    size_t max_lod = get_max_lod(ent->lod_dist, get_ent_dist(ent));
    size_t chosen = ~0ULL;
    dmat4 mvp;

    if ((max_lod == 0) && ent->render_is_rec)
        return;
    for (size_t i = 0; i < ent->sub.count; i++)
        entity3_render(ent->sub.ent[i], vp);
    for (size_t i = 0; i <= max_lod; i++)
        if (ent->render[i].mesh.m != NULL)
            chosen = i;
    if (chosen == ~0ULL)
        return;
    dmat4_mul(vp, ent->trans.world, mvp);
    render_obj_draw(ent->render[chosen],
    mvp, ent->trans.world, ent->trans.world_rot);
}
