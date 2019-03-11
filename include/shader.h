/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** gl shaders
*/

#ifndef _SHADER_H
#define _SHADER_H

int shader_check(gluint program, int is_program);
gluint shader_load_compute(const char *path);

gluint shader_load_vert_frag(const char *vertex_filepath,
const char *fragment_filepath);

#endif
