/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** ui_display_nbr
*/

#include "headers.h"

display_nbr_array_t ui_fill_display_nbr_array(int max_value, vec2 pos, float size, float offset_nbr)
{
    display_nbr_array_t res; 
    
    res.nb_digit = nbr_len((size_t)max_value, 0);
    res.digits = malloc_safe(sizeof(digit_array_t) * res.nb_digit);

    for (int i = 0; i < res.nb_digit; i++) {
        res.digits[i].value = 0;
        res.digits[i].digit = (button_t){UIRES_DIGIT_0, pos, size, -1.0f, BUTTON_REL_X};
        pos.x += offset_nbr;
    }
    return res;
}