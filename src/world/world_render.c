/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static void gl_set_stuff(demo_t *demo)
{
    refresh_vp(demo);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _lightmaps.base->id);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

static void gl_reset_stuff(void)
{
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

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

static void render_obj_draw(render_obj_t render)
{
    mesh_full_refresh(render.mesh);
    if (render.mesh->has_ext) {
        _demo->material[render.material].world();
        glBindVertexArray(render.mesh->gpu.vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, render.mesh->ext_count);
    } else {
        _demo->material[render.material].entity();
        glBindVertexArray(render.mesh->mesh->gpu.vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, render.mesh->mesh->vertex_count);
    }
}

static void entity3_render(entity3 *ent)
{
    size_t chosen;
    int do_draw = 0;

    for (size_t i = 0; i < ent->sub.count; i++)
        entity3_render(ent->sub.ent[i]);
    for (size_t i = 0; i < 3; i++) {
        do_draw |= ent->render[i].mesh != NULL;
        if (ent->render[i].mesh != NULL)
            chosen = i;
    }
    if (!do_draw)
        return;
    render_obj_draw(ent->render[chosen]);
}

static void chunk_render(chunk_t *chunk)
{
    entity3_render(chunk->ents);
}

void world_render(demo_t *demo)
{
    world_chunk_god(demo);
    gl_set_stuff(demo);
    for (size_t i = 0; i < demo->world.chunk_count; i++)
        chunk_render(demo->world.chunk[i]);
    gl_reset_stuff();
}
