/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** dialogue
*/

#include "headers.h"

const text_src_t text_array[] = {
    {TEXT_TEST, "Gretting you sick fucker and welcome in the sabondi's island"},
    {0, NULL}
};

void iu_text_init(void)
{
    for (int i = 0; i < TEXT_END; i++)
        _iu.text[i] = NULL;
    for (int i = 0; text_array[i].src != NULL; i++)
        _iu.text[text_array[i].index] =
        text_array[i].src;
}