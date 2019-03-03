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

#define INT_BITS_TO_FLOAT(value) (*((float*)(int32_t[]){value}))
#define FLOAT_BITS_TO_INT(value) (*((int32_t*)(float[]){value}))

#endif
