/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** gllol
*/

#include "headers.h"

float vec3_dot(vec3 a, vec3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

vec3 vec3_cross(vec3 a, vec3 b)
{
    return (vec3){a.y * b.z - a.z * b.y, -(a.x * b.z - a.z * b.x),
    a.x * b.y - a.y * b.x};
}

vec3 vec3_normalize(vec3 vec)
{
    float dist = sqrtf((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));

    return (vec3){vec.x / dist, vec.y / dist, vec.z / dist};
}

vec3 vec3_add(vec3 a, vec3 b)
{
    return (vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

vec3 vec3_sub(vec3 a, vec3 b)
{
    return (vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}
