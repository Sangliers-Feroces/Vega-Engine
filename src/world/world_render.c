/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static void gl_set_stuff(demo_t *demo)
{
    glint aperture;

    glUseProgram(demo->buf.world_shader);
    aperture = glGetUniformLocation(demo->buf.world_shader, "aperture");
    glUniform1f(aperture, _lightmaps.aperture);
    refresh_vp(demo, demo->buf.world_shader);
    glBindVertexArray(demo->buf.world_vertex_array);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _lightmaps.base->id);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

static void gl_reset_stuff(void)
{
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

static void chunk_lod_render_actual(octree *tree, size_t *ndx)
{
    if (tree == NULL)
        return;
    for (size_t i = 0; i < 8; i++)
        chunk_lod_render_actual(tree->sub[i], ndx);
    for (size_t i = 0; i < tree->triangles.count; i++) {
        glBindTexture(GL_TEXTURE_2D,
        tree->triangles.triangle[i]->albelo.texture->id);
        glDrawArrays(GL_TRIANGLES, (*ndx) * 3, 3);
        (*ndx)++;
    }
}

static void chunk_lod_render(chunk_lod_t *lod)
{
    size_t ndx = 0;

    if (lod->do_reupload_buf)
        chunk_lod_reupload_buf(lod);
    glBindBuffer(GL_ARRAY_BUFFER, lod->vertex_buffer);
    glActiveTexture(GL_TEXTURE1);
    chunk_lod_render_actual(lod->tree, &ndx);
}

static void chunk_render(chunk_t *chunk)
{
    chunk_lod_render(&chunk->lod[0]);
}

void world_render(demo_t *demo)
{
    gl_set_stuff(demo);
    for (size_t i = 0; i < demo->world.chunk_count; i++)
        chunk_render(demo->world.chunk[i]);
    gl_reset_stuff();
}
