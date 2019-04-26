/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static const trigger_on_hit_desc_t desc[] = {
    {TRIGGER_ON_HIT_NONE, NULL}
};

void world_trigger_init(void)
{
    for (size_t i = 0; i < TRIGGER_ON_HIT_MAX; i++)
        _demo->world.trigger_on_hit[i] = NULL;
    for (size_t i = 0; desc[i].trigger != TRIGGER_ON_HIT_NONE; i++)
        _demo->world.trigger_on_hit[desc[i].trigger] = desc[i].on_hit;
}
