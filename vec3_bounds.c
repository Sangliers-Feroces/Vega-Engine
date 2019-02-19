/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** gllol
*/

#include "headers.h"

/* checks whether a point or a collection of points is included in a cube */

int vec3_is_in_bounds(vec3 p, bounds3 bounds)
{
    return (
    (p.x >= bounds.min.x) && (p.y >= bounds.min.y) && (p.z >= bounds.min.z) &&
    (p.x < bounds.max.x) && (p.y < bounds.max.y) && (p.z < bounds.max.z));
}

int is_triangle_in_bounds(vec3 *triangle, bounds3 bounds)
{
    for (size_t i = 0; i < 3; i++)
        if (!vec3_is_in_bounds(triangle[i], bounds))
            return 0;
    return 1;
}
