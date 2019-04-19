/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** gllol
*/

#include "headers.h"

void dmat4_scale_trans(dvec3 pos, dvec3 scale, dmat4 res)
{
    dmat4 trans;

    dmat4_identity(res);
    res[0][0] = scale.x;
    res[1][1] = scale.y;
    res[2][2] = scale.z;
    dmat4_identity(trans);
    trans[3][0] = pos.x;
    trans[3][1] = pos.y;
    trans[3][2] = pos.z;
    dmat4_mul(trans, res, res);
}

static void rot_yx(double x, double y, dmat4 res)
{
    double c, s;
    dmat4 rot_x;

    dmat4_identity(res);
    c = cos(y);
    s = sin(y);
    res[0][0] = c;
    res[2][0] = -s;
    res[0][2] = s;
    res[2][2] = c;
    dmat4_identity(rot_x);
    c = cos(x);
    s = sin(x);
    rot_x[1][1] = c;
    rot_x[2][1] = s;
    rot_x[1][2] = -s;
    rot_x[2][2] = c;
    dmat4_mul(rot_x, res, res);
}

void dmat4_rot(dvec3 rot, dmat4 res)
{
    double c, s;
    dmat4 rot_z;

    rot_yx(rot.x, rot.y, res);
    dmat4_identity(rot_z);
    c = cos(rot.z);
    s = sin(rot.z);
    rot_z[0][0] = c;
    rot_z[0][1] = -s;
    rot_z[1][0] = s;
    rot_z[1][1] = c;
    dmat4_mul(rot_z, res, res);
}

void dmat4_model(dvec3 pos, dvec3 scale, dvec3 rot, dmat4 res)
{
    dmat4 scale_trans;

    dmat4_rot(rot, res);
    dmat4_scale_trans(pos, scale, scale_trans);
    dmat4_mul(scale_trans, res, res);
}

void dmat4_view(dvec3 pos, dvec3 rot, dmat4 res)
{
    dmat4 rot_mat;

    dmat4_identity(res);
    res[3][0] = -pos.x;
    res[3][1] = -pos.y;
    res[3][2] = -pos.z;
    dmat4_rot((dvec3){-rot.x, -rot.y, -rot.z}, rot_mat);
    dmat4_mul(rot_mat, res, res);
}
