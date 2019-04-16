/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** gllol
*/

#include "headers.h"

float dvec3_dot(dvec3 a, dvec3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float dvec3_norm(dvec3 vec)
{
    return sqrtf((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
}

float dvec3_dist(dvec3 a, dvec3 b)
{
    return dvec3_norm(dvec3_sub(a, b));
}

dvec3 dvec3_cross(dvec3 a, dvec3 b)
{
    return (dvec3){a.y * b.z - a.z * b.y, -(a.x * b.z - a.z * b.x),
    a.x * b.y - a.y * b.x};
}

dvec3 dvec3_normalize(dvec3 vec)
{
    float dist = dvec3_norm(vec);

    if (dist == 0.0)
        return (dvec3){0.0, 0.0, 0.0};
    return (dvec3){vec.x / dist, vec.y / dist, vec.z / dist};
}
