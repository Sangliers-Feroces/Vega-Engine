/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** gllol
*/

#include "headers.h"

void dmat4_mat4(dmat4 src, mat4 dst)
{
    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            dst[i][j] = src[i][j];
}

dmat4_w dmat4_dmat4_w(dmat4 src)
{
    dmat4_w res;

    memcpy(res.data, src, 16 * sizeof(double));
    return res;
}
