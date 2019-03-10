/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** vulkan ftw
*/

#include "headers.h"

static void gen_2d_texture_from_mem(gpu_serial_t serial)
{
    glint max;

    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R32I, max, serial.size / max + 1,
    0, GL_RED_INTEGER, GL_INT, NULL);
}

static void set_params_for_compute(gpu_serial_t serial, gluint mem)
{
    gen_2d_texture_from_mem(serial);
    glBindImageTexture(0, mem, 0, GL_FALSE, 0, GL_READ_ONLY, GL_R32I);
    glBindTexture(GL_TEXTURE_2D, _lightmaps.base->id);
    glBindImageTexture(0, _lightmaps.base->id, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
}

void gpu_compute_lightmap(octree *tree, size_t rays)
{
    gluint shader = shader_load_compute("src/gpu/shader/compute_lightmap.glsl");
    gluint mem;
    gpu_serial_t serial = octree_serialize(tree);

    glUseProgram(shader);
    glGenTextures(1, &mem);
    glBindTexture(GL_TEXTURE_2D, mem);
    gl_set_texture_parameters();
    set_params_for_compute(serial, mem);
    glDispatchCompute(1, 1, 1);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
    glBindImageTexture(0, 0, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);
    glDeleteProgram(shader);
    glDeleteTextures(1, &mem);
    free(serial.data);
    glBindTexture(GL_TEXTURE_2D, _lightmaps.base->id);
    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_FLOAT, _lightmaps.base->pixel);
    glFinish();
}
