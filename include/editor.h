/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#ifndef _EDITOR_H
#define _EDITOR_H

void editor(demo_t *demo);

void editor_init(demo_t *demo);
void editor_quit(demo_t *demo);

void editor_select_point(demo_t *demo, vec3 p);
void editor_remove_point(demo_t *demo, vec3 p);

void editor_select(demo_t *demo, inter_ray3 inter);

void editor_paint(demo_t *demo, inter_ray3 inter);

#endif