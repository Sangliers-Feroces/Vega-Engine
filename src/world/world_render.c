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

static void chunk_render(chunk_t *chunk)
{
    entity3_update(chunk->ents);
    entity3_render(chunk->ents, _demo->cam.mvp.vp);
}

void world_render(demo_t *demo)
{
    world_chunk_god(demo);
    gl_set_stuff(demo);
    for (size_t i = 0; i < demo->world.chunk_count; i++)
        chunk_render(demo->world.chunk[i]);
    render_delay_exec();
    gl_reset_stuff();
}
