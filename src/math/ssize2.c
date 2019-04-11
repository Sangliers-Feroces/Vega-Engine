/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** gllol
*/

#include "headers.h"

ssize2 ssize2_add(ssize2 a, ssize2 b)
{
    return (ssize2){a.x + b.x, a.y + b.y};
}

ssize2 ssize2_sub(ssize2 a, ssize2 b)
{
    return (ssize2){a.x - b.x, a.y - b.y};
}
