/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** std::vector
*/

#ifndef _RTX_H
#define _RTX_H

int is_ray_in_bounds(ray3 ray, bounds3 bounds);
int is_ray_in_bounds_seg(ray3 ray, bounds3 bounds);

rtx_triangle* rtx_triangle_create(vec3 *triangle);
rtx_triangle* rtx_triangle_create_param(vec3 *triangle, int alloc_lightmap);
rtx_triangle* rtx_triangle_create_discrete(vec3 a, vec3 b, vec3 c);
void rtx_triangle_destroy(rtx_triangle *triangle);

void vec_rtx_triangle_add(vec_rtx_triangle *vec, rtx_triangle *to_add);
void vec_rtx_triangle_destroy(vec_rtx_triangle vec);

vec_rtx_triangle vec_rtx_triangle_create(void);
void vec_rtx_triangle_add(vec_rtx_triangle *vec, rtx_triangle *to_add);
void vec_rtx_triangle_destroy(vec_rtx_triangle vec);
void vec_rtx_triangle_free(vec_rtx_triangle vec);

#endif
