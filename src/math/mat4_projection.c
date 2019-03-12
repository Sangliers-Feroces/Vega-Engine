/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** gllol
*/

#include "headers.h"

void mat4_perspective(proj_t proj, mat4 res)
{
    float tan_half_fov_w = tanf(proj.fov_w * (M_PI / 180.0f) / 2.0f);

    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            res[i][j] = 0.0f;
    res[0][0] = 1.0f / (proj.ratio_wh * tan_half_fov_w);
    res[1][1] = 1.0f / tan_half_fov_w;
    res[2][2] = proj.far_plane / (proj.far_plane - proj.near_plane);
    res[2][3] = 1.0f;
    res[3][2] = - (proj.near_plane * proj.far_plane) /
    (proj.far_plane - proj.near_plane);
    return;
}
