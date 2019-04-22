/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** vg_text_struct
*/

#pragma once

typedef enum {
    IUCADRE_BLACK,
    IUCADRE_END
} iucadre_t;

typedef enum {
    TEXT_TEST,
    TEXT_TEST_2,
    TEXT_END
} text_index_t;

typedef struct {
    text_index_t index;
    char *src;
} text_src_t;

typedef enum {
    TEXT_GRP_IND_WELCOME,
    TEXT_IND_END
} text_grp_ind_t;

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

typedef struct {
    char *str;
    //ptr function
} dialogue_text;

typedef struct {
    int read;
    int read_head;
    int nb_texts;
    font_list_t font_index;
    rect_t pos_size;
    dialogue_text *texts;
    iucadre_t cadre;
    //choices
    int choices;
    iucadre_t cadre_choice;
    dialogue_text choices_display[2];
} vg_dialogue;