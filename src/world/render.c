/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static void gl_set_stuff(void)
{
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
    entity3_render(chunk->ents, _demo->cam.mvp.vp);
}

void world_render(void)
{
    gl_set_stuff();
    dmat4_copy(_demo->world.camera->trans.world,
    _demo->world.skybox->trans.world);
    for (size_t i = 0; i < _demo->world.chunk_count; i++)
        chunk_render(_demo->world.chunk[i]);
    entity3_render(_demo->world.ents, _demo->cam.mvp.vp);
    render_delay_exec();
    gl_reset_stuff();
}
