/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#ifndef _DEMO_H
#define _DEMO_H

#define CAM_MOVE 0.2f;

void demo_init_input(demo_t *demo);
void demo_poll_input(demo_t *demo);

demo_t* demo_init(octree *tree);
void demo_quit(demo_t *demo);

int demo_loop(octree *tree);

void demo_render(demo_t *demo);

#endif
