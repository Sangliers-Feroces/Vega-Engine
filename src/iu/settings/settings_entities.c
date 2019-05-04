/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** settings_entities
*/

#include "headers.h"

void setting_set_entities(void)
{
    entity_constructor(&_iu.settings.entities[SETTINGS_BG], (entity2_param_t){
    IUTEX_SETTINGS_BG, (rect_t){{-1.0f, -1.0f}, {2.0f, 2.0f}}, -0.997});
    return;
}