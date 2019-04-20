/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

void material_fun_grass_world(dmat4 mvp)
{
    shader_set(SHADER_WORLD, mvp);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _demo->tex[TEX_GRASS]->id);
}

void material_fun_grass_entity(dmat4 mvp)
{
    shader_set(SHADER_WORLD, mvp);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _demo->tex[TEX_GRASS]->id);
}
