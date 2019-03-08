/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** gllol
*/

#include "headers.h"

void mat4_trans_scale(vec3 pos, vec3 scale, mat4 res)
{
    mat4_identity(res);
    res[0][0] = scale.x;
    res[1][1] = scale.y;
    res[2][2] = scale.z;
    res[3][0] = pos.x;
    res[3][1] = pos.y;
    res[3][2] = pos.z;
}

static void rot_xy(float x, float y, mat4 res)
{
    float cos, sin;
    mat4 rot_x;

    mat4_identity(res);
    cos = cosf(y);
    sin = sinf(y);
    res[0][0] = cos;
    res[2][0] = -sin;
    res[0][2] = sin;
    res[2][2] = cos;
    mat4_identity(rot_x);
    cos = cosf(x);
    sin = sinf(x);
    rot_x[1][1] = cos;
    rot_x[2][1] = sin;
    rot_x[1][2] = -sin;
    rot_x[2][2] = cos;
    mat4_mul(rot_x, res, res);
}

void mat4_rot(vec3 rot, mat4 res)
{
    float cos, sin;
    mat4 rot_z;

    rot_xy(rot.x, rot.y, res);
    mat4_identity(rot_z);
    cos = cosf(rot.z);
    sin = sinf(rot.z);
    mat4_mul(rot_z, res, res);
}

void mat4_model(vec3 pos, vec3 scale, vec3 rot, mat4 res)
{
    mat4 trans_scale;

    mat4_rot(rot, res);
    mat4_trans_scale(pos, scale, trans_scale);
    mat4_mul(trans_scale, res, res);
}

void mat4_view(vec3 pos, vec3 rot, mat4 res)
{
    mat4 trans;

    mat4_rot((vec3){-rot.x, -rot.y, -rot.z}, res);
    mat4_identity(trans);
    res[3][0] = -pos.x;
    res[3][1] = -pos.y;
    res[3][2] = -pos.z;
    mat4_mul(trans, res, res);
}
