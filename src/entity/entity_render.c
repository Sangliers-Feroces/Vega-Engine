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

static void render_obj_draw(render_obj_t render, dmat4 mvp, dmat4 world, dmat4 rot)
{
    mesh_full_refresh(render.mesh.m);
    if (render.mesh.m->has_ext) {
        _demo->material[render.material].world(mvp, world, rot);
        glBindVertexArray(render.mesh.m->gpu.vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, render.mesh.m->ext_count);
    } else {
        _demo->material[render.material].entity(mvp, world, rot);
        glBindVertexArray(render.mesh.m->mesh->gpu.vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, render.mesh.m->mesh->vertex_count);
    }
}

void entity3_render(entity3 *ent, dmat4 vp)
{
    size_t chosen;
    int do_draw = 0;
    dmat4 mvp;

    dmat4_mul(vp, ent->trans.world, mvp);
    for (size_t i = 0; i < ent->sub.count; i++)
        entity3_render(ent->sub.ent[i], vp);
    for (size_t i = 0; i < 3; i++) {
        do_draw |= ent->render[i].mesh.m != NULL;
        if (ent->render[i].mesh.m != NULL)
            chosen = i;
    }
    if (!do_draw)
        return;
    render_obj_draw(ent->render[chosen],
    mvp, ent->trans.world, ent->trans.world_rot);
}
