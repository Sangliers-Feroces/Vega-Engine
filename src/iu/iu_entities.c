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
    IUTEX_INVENT_BG, (rect_t){{-1.0f, -1.0f},{2.0f, 2.0f}}, -0.999});
}