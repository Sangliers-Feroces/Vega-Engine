/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#ifndef _EDITOR_H
#define _EDITOR_H

#define EDITOR_EXTRUSION_OFF 0.1f

void editor(demo_t *demo);

void editor_init(demo_t *demo);
void editor_quit(demo_t *demo);

void editor_select_point(demo_t *demo, vec3 p);
void editor_remove_point(demo_t *demo, vec3 p);

void editor_select(demo_t *demo, inter_ray3 inter);

void editor_paint(demo_t *demo, inter_ray3 inter);

void editor_load_models(demo_t *demo);
void editor_free_models(demo_t *demo);

void editor_draw(demo_t *demo);

void editor_grab(demo_t *demo);
vec3 editor_grab_get_proj(demo_t *demo);
void editor_grab_update_delta(demo_t *demo);

void editor_grab_apply(demo_t *demo);

void editor_grab_replace(demo_t *demo);

int editor_is_point_selected(demo_t *demo, vec3 p);
void editor_del(demo_t *demo);

int rtx_triangle_is_selected(demo_t *demo, rtx_triangle *triangle);
void editor_flip(demo_t *demo);

void editor_extrude(demo_t *demo);

void editor_rot(demo_t *demo);

void rtx_triangle_uv(rtx_triangle *triangle);
void editor_uv(demo_t *demo);

#endif
