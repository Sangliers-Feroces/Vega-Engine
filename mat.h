/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** headers
*/

#ifndef _MAT_H
#define _MAT_H

/* math-related prototypes */

int vec3_is_in_bounds(vec3 p, bounds3 bounds);
int is_triangle_in_bounds(vec3 *triangle, bounds3 bounds);

float vec3_dot(vec3 a, vec3 b);
vec3 vec3_cross(vec3 a, vec3 b);
vec3 vec3_normalize(vec3 vec);
vec3 vec3_add(vec3 a, vec3 b);
vec3 vec3_sub(vec3 a, vec3 b);

vec3 ray3_compute(ray3 ray, float t);

vec3 barycentric3(vec3 p, vec3 *triangle);
int is_point_in_triangle(vec3 p, vec3 *triangle);

#endif
