/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** iu_text
*/

#include "headers.h"

void iu_display_text(char *src)
{
    printf("%s\n", src);
}

void iu_display_grp(text_grp_ind_t index)
{
    int j = 0;
    int i = 0;

    if (_iu.text_grp[index].used == 1)
        return;
    while (i < _iu.text_grp[index].nb_text_displyed) {
        if (_demo->input.key_press[KEY_ENTER]) {
            i++;
        }
        if (j == 0)
            iu_display_text(_iu.text[_iu.text_grp[index].start_text + i]);
        j++;
    }
    _iu.text_grp[index].used = 1;
}