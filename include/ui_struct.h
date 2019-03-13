/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** ui_struct
*/

#ifndef UI_STRUCT_H_
#define UI_STRUCT_H_

typedef struct {
    float width;
    float lenght;
} quad_size_t;

typedef struct {
    gluint ui_program;
    gluint vertex_buffer;
    texture2 *tex;
    float ratiowh;
} ui_struct;

#endif /* !UI_STRUCT_H_ */
