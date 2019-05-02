/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** stat_display
*/

#include "headers.h"

void invent_stat_display_init(void)
{
    for (int i = 0; i < STAT_END; i++) {
        _iu.invent.stats[i] = vg_text_create(NULL, NULL);
        vg_text_set_position(&_iu.invent.stats[i],
        (vec2){-0.50f, -0.30f + (i * -0.05f)});
        vg_text_set_size(&_iu.invent.stats[i], (vec2){0.02f, 0.03f});
    }
    vg_text_reset_str(&_iu.invent.stats[STAT_HP], "HP:40", " +20");
    vg_text_reset_str(&_iu.invent.stats[STAT_MANA], "MANA:200", " -30");
}