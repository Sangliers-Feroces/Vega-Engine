/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

trigger_t* trigger_create(dvec3 min, dvec3 max, trigger_on_hit_t on_hit)
{
    trigger_t *res =
    (trigger_t*)malloc_safe(sizeof(trigger_t));

    res->min = min;
    res->max = max;
    res->on_hit = on_hit;
    res->ent = NULL;
    res->ndx = ~0ULL;
    return res;
}

void trigger_destroy(trigger_t *trigger)
{
    if (trigger == NULL)
        return;
    if (trigger->ndx != ~0ULL) {
        _demo->world.triggers.trigger[trigger->ndx] =
        _demo->world.triggers.trigger[--_demo->world.triggers.count];
        _demo->world.triggers.trigger[trigger->ndx]->ndx = trigger->ndx;
    }
    free(trigger);
}
