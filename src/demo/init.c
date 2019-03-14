/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** various loaders : valid within a gl context
*/

#include "headers.h"

void init(void)
{
    thread_init();
    srand(time(NULL));
    load_gl_fun();
    glEnable(GL_CULL_FACE);
    lightmap_init();
}

void quit(void)
{
    thread_quit();
    lightmap_quit();
}
