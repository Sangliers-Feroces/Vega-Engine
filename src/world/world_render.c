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
    refresh_vp(demo);
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

static void chunk_lod_render_actual(octree *tree, size_t *ndx, size_t *first, material_t *material)
{
    material_t cur;

    if (tree == NULL)
        return;
    for (size_t i = 0; i < 8; i++)
        chunk_lod_render_actual(tree->sub[i], ndx, first, material);
    for (size_t i = 0; i < tree->triangles.count; i++) {
        cur = tree->triangles.triangle[i]->material;
        if (cur != (*material)) {
            if ((*material) != ~0U) {
                _demo->material[*material].world();
                glDrawArrays(GL_TRIANGLES, (*first) * 3, ((*ndx) - (*first)) * 3);
            }
            *material = cur;
            *first = *ndx;
        }
        (*ndx)++;
    }
}

static void chunk_lod_render(chunk_lod_t *lod)
{
    size_t ndx = 0;
    material_t material = ~0U;
    size_t first = 0;

    if (lod->do_reupload_buf)
        chunk_lod_reupload_buf(lod);
    if (lod->vertex_count < 3)
        return;
    glBindVertexArray(lod->vertex_array);
    glBindBuffer(GL_ARRAY_BUFFER, lod->vertex_buffer);
    chunk_lod_render_actual(lod->tree, &ndx, &first, &material);
    if (material != ~0U) {
        _demo->material[material].world();
        glDrawArrays(GL_TRIANGLES, first * 3, (ndx - first) * 3);
    }
    //glBindTexture(GL_TEXTURE_2D, _iu.textures[IUTEX_TERRAIN]->id);
    //glDrawArrays(GL_TRIANGLES, 0, lod->vertex_count);
}

static void chunk_render(chunk_t *chunk)
{
    float dist = vec2_dist(
    (vec2){chunk->pos.x * CHUNK_SIZE + CHUNK_SIZE / 2.0f,
    chunk->pos.y * CHUNK_SIZE + CHUNK_SIZE / 2.0f},
    (vec2){_demo->cam.pos.x, _demo->cam.pos.z});

    if (dist < 1500.0f)
        chunk_lod_render(&chunk->lod[2]);
    else if (dist < 3000.0f)
        chunk_lod_render(&chunk->lod[1]);
    else
        chunk_lod_render(&chunk->lod[0]);
}

void world_render(demo_t *demo)
{
    world_chunk_god(demo);
    gl_set_stuff(demo);
    for (size_t i = 0; i < demo->world.chunk_count; i++)
        chunk_render(demo->world.chunk[i]);
    gl_reset_stuff();
}
