/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** iu_text_struct
*/

#pragma once

typedef enum {
    TEXT_TEST,
    TEXT_END
} text_t;

typedef struct {
    text_t index;
    char *src;
} text_src_t;