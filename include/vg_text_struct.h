/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** vg_text_struct
*/

#pragma once

typedef enum {
    FONT_MINECRAFT,
    FONT_END
} font_list_t;

typedef struct {
    char *str;
    char *value;
    font_list_t font_index;
    rect_t pos_size;
} vg_text;

typedef enum {
    TEXT_TEST,
    TEXT_TEST_2,
    TEXT_END
} text_index_t;

typedef enum {
    TEXT_GRP_IND_WELCOME,
    TEXT_IND_END
} text_grp_ind_t;

typedef struct {
    int nb_text_displyed;
    int nb_text_all; //all text possible if choice -> count all the choices
    text_index_t start_text;
    int used;
    //choix
    //int is_choice;
    //int offset_choice;
} text_grp_t;

typedef struct {
    text_index_t index;
    char *src;
} text_src_t;

typedef struct {
    int count;
    text_grp_t text_grp[TEXT_IND_END];
} text_t;