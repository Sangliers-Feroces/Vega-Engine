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
vec2 vec2_adds(vec2 vec, float value);
vec2 vec2_sub(vec2 a, vec2 b);
vec2 vec2_subs(vec2 vec, float value);
vec2 vec2_min(vec2 a, vec2 b);
vec2 vec2_max(vec2 a, vec2 b);
vec2 vec2_muls(vec2 vec, float value);

vec2 vec2_mul(vec2 a, vec2 b);
vec2 vec2_div(vec2 a, vec2 b);
vec2 vec2_divs(vec2 vec, float value);
float vec2_norm(vec2 vec);
float vec2_dist(vec2 a, vec2 b);

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
vec3 vec3_divs(vec3 vec, float value);

vec3 ray3_compute(ray3 ray, float t);

vec4 vec4_add(vec4 a, vec4 b);
vec4 vec4_sub(vec4 a, vec4 b);
vec4 vec4_muls(vec4 vec, float value);

void mat4_identity(mat4 dst);
void mat4_copy(mat4 src, mat4 dst);
void mat4_mul(mat4 a, mat4 b, mat4 res);

void mat4_scale_trans(vec3 pos, vec3 scale, mat4 res);
void mat4_rot(vec3 rot, mat4 res);
void mat4_model(vec3 pos, vec3 scale, vec3 rot, mat4 res);
void mat4_view(vec3 pos, vec3 rot, mat4 res);
vec4 mat4_mul_vec(mat4 a, vec4 b);

void mat4_perspective(proj_t proj, mat4 res);
void mat4_ortho(proj_t proj, mat4 res);

vec2 barycentric2_get_point(vec2 *triangle, vec3 bar);

vec3 barycentric3(vec3 p, vec3 *triangle);
int is_point_in_triangle(vec3 p, vec3 *triangle);
int is_barycentric_valid(vec3 bar);
int is_point_in_triangle_get_bar(vec3 p, vec3 *triangle, vec3 *bar);

int is_barycentric_valid_laxist(vec3 bar);
int is_point_in_triangle_laxist(vec3 p, vec3 *triangle);

vec2 circle_intersect(circle a, circle b);

vec3 spherical_to_cartesian_z(vec3 spherical);
vec3 spherical_to_cartesian_z_to_x(vec3 spherical);

int rect_is_vec2_inside(rect_t rect, vec2 vec);

vec3 vec3_interpolate(vec3 a, vec3 b, long double ratio);

#endif
