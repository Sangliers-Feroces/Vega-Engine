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
    glFrontFace(GL_CW);
    glPolygonMode(GL_BACK, GL_LINE);
    lightmap_init();
}

void quit(void)
{
    thread_quit();
    lightmap_quit();
}
