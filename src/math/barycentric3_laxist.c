/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** optiiiiiii rtx
*/

#include "headers.h"

static int is_float_in_0_1(float value)
{
    float laxistness = 0.1f;
    return (value >= (- laxistness)) && (value <= 1.0f + (laxistness));
}

int is_point_in_triangle_laxist(vec3 p, vec3 *triangle)
{
    vec3 bar = barycentric3(p, triangle);

    return (is_float_in_0_1(bar.x) && is_float_in_0_1(bar.y) &&
    is_float_in_0_1(bar.z));
}

int is_barycentric_valid_laxist(vec3 bar)
{
    return (is_float_in_0_1(bar.x) && is_float_in_0_1(bar.y) &&
    is_float_in_0_1(bar.z));
}
