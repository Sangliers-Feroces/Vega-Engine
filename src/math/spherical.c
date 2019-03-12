/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** gllol
*/

#include "headers.h"

vec3 spherical_to_cartesian_z(vec3 spherical)
{
    vec3 res;

    res.x = -sinf(spherical.y) * cosf(spherical.x);
    res.z = cosf(spherical.y) * cosf(spherical.x);
    res.y = sinf(spherical.x);
    return res;
}

vec3 spherical_to_cartesian_z_to_x(vec3 spherical)
{
    vec3 res;

    res.x = -sinf(spherical.y - M_PI_2);
    res.z = cosf(spherical.y - M_PI_2);
    res.y = 0.0;
    return res;
}
