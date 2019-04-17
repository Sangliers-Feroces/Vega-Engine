/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

void material_fun_water_world(void)
{
    glUseProgram(_demo->shader[SHADER_WATER]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _iu.textures[IUTEX_WATER]->id);
}

void material_fun_water_entity(void)
{
    glUseProgram(_demo->shader[SHADER_WATER]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _iu.textures[IUTEX_WATER]->id);
}
