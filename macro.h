/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** macros stuff !
*/

#ifndef _MACRO_H
#define _MACRO_H

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define CLAMP(value, min, max) (MIN(MAX((value), (min)), (max)))

#define FLT_INF (*((float*)(uint32_t[]){0x7F800000}))

#endif
