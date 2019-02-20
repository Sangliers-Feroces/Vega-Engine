/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** optiiiiiii rtx
*/

#include "headers.h"

/* barycentric coordinatates are useful to know whether a point is located  */
/* in a triangle or not.                                                    */
/* they show how close the point is from every point of the triangle,       */
/* we can use that to interpolate triangle's attributes (uv for example)    */

vec3 barycentric3(vec3 p, vec3 *triangle)
{
    vec3 v0 = vec3_sub(triangle[1], triangle[0]);
    vec3 v1 = vec3_sub(triangle[2], triangle[0]);
    vec3 v2 = vec3_sub(p, triangle[0]);
    float dot00 = vec3_dot(v0, v0);
    float dot01 = vec3_dot(v0, v1);
    float dot11 = vec3_dot(v1, v1);
    float dot20 = vec3_dot(v2, v0);
    float dot21 = vec3_dot(v2, v1);
    float div = dot00 * dot11 - dot01 * dot01;
    vec3 res;

    res.y = (dot11 * dot20 - dot01 * dot21) / div;
    res.z = (dot00 * dot21 - dot01 * dot20) / div;
    res.x = 1.0f - res.y - res.z;
    return res;
}

static int is_float_in_0_1(float value)
{
    return ((value >= 0.0f) && (value <= 1.0f));
}

int is_point_in_triangle(vec3 p, vec3 *triangle)
{
    vec3 bar = barycentric3(p, triangle);

    return (is_float_in_0_1(bar.x) && is_float_in_0_1(bar.y) &&
    is_float_in_0_1(bar.z));
}
