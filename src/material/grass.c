/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

void material_fun_grass_world(void)
{
    glUseProgram(_demo->shader[SHADER_WORLD]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _iu.textures[IUTEX_TERRAIN]->id);
}

void material_fun_grass_entity(void)
{
    glUseProgram(_demo->shader[SHADER_WORLD]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _iu.textures[IUTEX_TERRAIN]->id);
}
