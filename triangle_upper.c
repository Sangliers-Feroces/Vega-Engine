/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** gllol
*/

#include "headers.h"

size_t get_point_side(vec3 p, bounds3 bounds)
{
    return !((p.x >= bounds.min.x) && (p.y >= bounds.min.y)
    && (p.z >= bounds.min.z)) ? 0 : 7;
}

size_t get_triangle_upper_tree(vec3 *triangle, bounds3 bounds)
{
    for (size_t i = 0; i < 3; i++)
        if (!vec3_is_in_bounds(triangle[i], bounds))
            return get_point_side(triangle[i], bounds);
    return 0;
}
