/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** gllol
*/

#include "headers.h"

void dmat4_perspective(proj_t proj, dmat4 res)
{
    double tan_half_fov_w = tan(proj.fov_w * (M_PI / 180.0) / 2.0);

    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            res[i][j] = 0.0;
    res[0][0] = 1.0 / (proj.ratio_wh * tan_half_fov_w);
    res[1][1] = 1.0 / tan_half_fov_w;
    res[2][2] = (proj.far_plane + proj.near_plane) /
    (proj.far_plane - proj.near_plane);
    res[2][3] = 1.0;
    res[3][2] = - (2.0 * proj.near_plane * proj.far_plane) /
    (proj.far_plane - proj.near_plane);
    return;
}

void dmat4_ortho(proj_t proj, dmat4 res)
{
    double w = proj.fov_w * proj.ratio_wh;
    double h = proj.fov_w;

    dmat4_identity(res);
    res[0][0] = 2.0f / (w);
    res[1][1] = 2.0f / (h);
    res[2][2] = 2.0f / (proj.far_plane - proj.near_plane);
    res[3][2] = - (proj.far_plane + proj.near_plane) /
    (proj.far_plane - proj.near_plane);
}
