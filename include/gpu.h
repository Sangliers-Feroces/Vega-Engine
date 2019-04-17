/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** gl stuff
*/

#ifndef _GPU_H
#define _GPU_H

void gpu_compute_lightmap(octree *tree, size_t rays);

void shader_init(demo_t *demo);
void shader_quit(demo_t *demo);
void material_init(demo_t *demo);

#endif
