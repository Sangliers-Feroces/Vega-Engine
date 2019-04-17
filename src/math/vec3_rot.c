/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** gllol
*/

#include "headers.h"

void mat4_rot_xy(dvec3 rot, mat4 res)
{
    float cos, sin;
    mat4 rot_x;

    mat4_identity(res);
    cos = cosf(rot.x);
    sin = sinf(rot.x);
    res[1][1] = cos;
    res[2][1] = sin;
    res[1][2] = -sin;
    res[2][2] = cos;
    mat4_identity(rot_x);
    cos = cosf(rot.y);
    sin = sinf(rot.y);
    rot_x[0][0] = cos;
    rot_x[2][0] = -sin;
    rot_x[0][2] = sin;
    rot_x[2][2] = cos;
    mat4_mul(rot_x, res, res);
}

dvec3 mat4_mul_dvec3(mat4 mat, dvec3 vec)
{
    vec4 used = {vec.x, vec.y, vec.z, 1.0f};
    vec4 res = mat4_mul_vec(mat, used);

    return (dvec3){res.x, res.y, res.z};
}
