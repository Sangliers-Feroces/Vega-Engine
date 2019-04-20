/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

void material_fun_water_world(dmat4 mvp)
{
    shader_set(SHADER_WATER, mvp);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _demo->tex[TEX_WATER]->id);
}

void material_fun_water_entity(dmat4 mvp)
{
    shader_set(SHADER_WATER, mvp);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _demo->tex[TEX_WATER]->id);
}
