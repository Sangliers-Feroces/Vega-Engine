/*
** EPITECH PROJECT, 2019
** MUL_my_world_2018
** File description:
** iu_entities
*/

#include "headers.h"

void set_entities(void)
{
    /*_iu.buttons[IUBUTTON_ELON] =
    (entity2_t){IUTEX_ELON, (rect_t){{-0.30f, 0.0f}, {0.1f, 0.1f}},
    -1.0f, IUREL_FULL};*/
    entity_constructor(&_iu.invent[IUINVENT_BG], (entity2_param_t){
    IUTEX_INVENT_BG, (rect_t){{-1.0f, -1.0f},{2.0f, 2.0f}}, -0.997});
    entity_constructor(&_iu.buttons[IUBUTTON_CADRE], (entity2_param_t){
    IUTEX_TEXT_CADRE, (rect_t){{-0.5f, -1.0f},{1.0f, 0.3f}}, -0.998});
}