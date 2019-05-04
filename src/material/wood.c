/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

void material_fun_wood_entity(dmat4 mvp, dmat4 world, dmat4 rot)
{
    shader_set(SHADER_WORLD, mvp, world, rot);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _demo->tex[TEX_WOOD]->id);
}
