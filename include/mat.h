/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** headers
*/

#ifndef _MAT_H
#define _MAT_H

/* math-related prototypes */

dvec3 normal3(dvec3 a, dvec3 b, dvec3 c);

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
int vec2_eq(vec2 a, vec2 b);

int dvec3_is_in_bounds(dvec3 p, bounds3 bounds);
int is_triangle_in_bounds(dvec3 *triangle, bounds3 bounds);

double dvec3_dot(dvec3 a, dvec3 b);
double dvec3_norm(dvec3 vec);
double dvec3_dist(dvec3 a, dvec3 b);
dvec3 dvec3_cross(dvec3 a, dvec3 b);
dvec3 dvec3_normalize(dvec3 vec);

dvec3 dvec3_add(dvec3 a, dvec3 b);
dvec3 dvec3_sub(dvec3 a, dvec3 b);
dvec3 dvec3_muls(dvec3 vec, double value);
dvec3 dvec3_divs(dvec3 vec, double value);
int dvec3_eq(dvec3 a, dvec3 b);

dvec3 dvec3_adds(dvec3 vec, double value);

dvec3 ray3_compute(ray3 ray, double t);

vec4 vec4_add(vec4 a, vec4 b);
vec4 vec4_sub(vec4 a, vec4 b);
vec4 vec4_muls(vec4 vec, double value);

void mat4_identity(mat4 dst);
void mat4_copy(mat4 src, mat4 dst);
void mat4_mul(mat4 a, mat4 b, mat4 res);

void mat4_scale_trans(dvec3 pos, dvec3 scale, mat4 res);
void mat4_rot(dvec3 rot, mat4 res);
void mat4_model(dvec3 pos, dvec3 scale, dvec3 rot, mat4 res);
void mat4_view(dvec3 pos, dvec3 rot, mat4 res);
vec4 mat4_mul_vec(mat4 a, vec4 b);

void mat4_perspective(proj_t proj, mat4 res);
void mat4_ortho(proj_t proj, mat4 res);

vec2 barycentric2_get_point(vec2 *triangle, dvec3 bar);

dvec3 barycentric3(dvec3 p, dvec3 *triangle);
int is_point_in_triangle(dvec3 p, dvec3 *triangle);
int is_barycentric_valid(dvec3 bar);
int is_point_in_triangle_get_bar(dvec3 p, dvec3 *triangle, dvec3 *bar);

int is_barycentric_valid_laxist(dvec3 bar);
int is_point_in_triangle_laxist(dvec3 p, dvec3 *triangle);

vec2 circle_intersect(circle a, circle b);

dvec3 spherical_to_cartesian_z(dvec3 spherical);
dvec3 spherical_to_cartesian_z_to_x(dvec3 spherical);

int rect_is_vec2_inside(rect_t rect, vec2 vec);

dvec3 dvec3_interpolate(dvec3 a, dvec3 b, long double ratio);

void mat4_rot_xy(dvec3 rot, mat4 res);
dvec3 mat4_mul_dvec3(mat4 mat, dvec3 vec);

ssize2 ssize2_add(ssize2 a, ssize2 b);
ssize2 ssize2_sub(ssize2 a, ssize2 b);
ssize2 ssize2_abs(ssize2 value);
ssize_t ssize2_dist_sq_man(ssize2 a, ssize2 b);

arr2d_dvec3_t arr2d_dvec3_create(size_t w, size_t h);
void arr2d_dvec3_destroy(arr2d_dvec3_t arr);
arr_dvec3_t arr_dvec3_create(size_t count);
void arr_dvec3_destroy(arr_dvec3_t arr);
void chunk_border_destroy(chunk_border_t border);

vec3 dvec3_vec3(dvec3 value);
dvec3 dvec3_init(double x, double y, double z);

#endif
