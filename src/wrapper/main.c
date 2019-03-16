/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** innocent main
*/

#include "xdworld.h"

int main(int argc, char **argv, char **env)
{
    if (env[0] == NULL)
        return (84);
    return (sftexture_createfromfile(argc, argv));
}
