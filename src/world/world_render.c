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

static void render_geom(material_t material, size_t first, size_t i)
{
    if (material != ~0U) {
        _demo->material[material].world();
        glDrawArrays(GL_TRIANGLES, first * 3, (i - first) * 3);
    }
}

static void chunk_lod_render(chunk_lod_t *lod)
{
    material_t material = ~0U;
    material_t cur;
    size_t first = 0;

    if (lod->do_reupload_buf)
        chunk_lod_reupload_buf(lod);
    glBindVertexArray(lod->vertex_array);
    glBindBuffer(GL_ARRAY_BUFFER, lod->vertex_buffer);
    for (size_t i = 0; i < lod->geom->count; i++) {
        cur = lod->geom->triangle[i]->material;
        if (cur != material) {
            render_geom(material, first, i);
            material = cur;
            first = i;
        }
    }
    render_geom(material, first, lod->geom->count);
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
