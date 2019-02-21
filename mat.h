/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** headers
*/

#ifndef _MAT_H
#define _MAT_H

/* math-related prototypes */

vec2 vec2_add(vec2 a, vec2 b);
vec2 vec2_sub(vec2 a, vec2 b);
vec2 vec2_min(vec2 a, vec2 b);
vec2 vec2_max(vec2 a, vec2 b);
vec2 vec2_muls(vec2 vec, float value);

int vec3_is_in_bounds(vec3 p, bounds3 bounds);
int is_triangle_in_bounds(vec3 *triangle, bounds3 bounds);

float vec3_dot(vec3 a, vec3 b);
float vec3_norm(vec3 vec);
float vec3_dist(vec3 a, vec3 b);
vec3 vec3_cross(vec3 a, vec3 b);
vec3 vec3_normalize(vec3 vec);

vec3 vec3_add(vec3 a, vec3 b);
vec3 vec3_sub(vec3 a, vec3 b);
vec3 vec3_muls(vec3 vec, float value);

vec3 ray3_compute(ray3 ray, float t);

vec2 barycentric2_get_point(vec2 *triangle, vec3 bar);

vec3 barycentric3(vec3 p, vec3 *triangle);
int is_point_in_triangle(vec3 p, vec3 *triangle);
int is_barycentric_valid(vec3 bar);
int is_point_in_triangle_get_bar(vec3 p, vec3 *triangle, vec3 *bar);

vec2 circle_intersect(circle a, circle b);

#endif
