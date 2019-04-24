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

static size_t get_max_lod(double dist)
{
    if (dist < (384.0 * 384.0))
        return 2;
    else if (dist < (768.0 * 768.0))
        return 1;
    else
        return 0;
}

static double get_ent_dist(entity3 *ent)
{
    dvec3 p = dmat4_mul_dvec3(ent->trans.world, dvec3_init(0.0, 0.0, 0.0));

    return dvec3_dist_sq(dvec3_init(p.x, 0.0, p.z),
    dvec3_init(_demo->cam.pos.x, 0.0, _demo->cam.pos.z));
}

void entity3_render(entity3 *ent, dmat4 vp)
{
    size_t max_lod = get_max_lod(get_ent_dist(ent));
    size_t chosen = ~0ULL;
    dmat4 mvp;

    dmat4_mul(vp, ent->trans.world, mvp);
    for (size_t i = 0; i < ent->sub.count; i++)
        entity3_render(ent->sub.ent[i], vp);
    for (size_t i = 0; i <= max_lod; i++)
        if (ent->render[i].mesh.m != NULL)
            chosen = i;
    if (chosen == ~0ULL)
        return;
    render_obj_draw(ent->render[chosen],
    mvp, ent->trans.world, ent->trans.world_rot);
}
