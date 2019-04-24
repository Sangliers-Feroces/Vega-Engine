/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

trigger_t* trigger_create(dvec3 size,
void (*on_hit)(entity3 *ent, entity3 *other))
{
    trigger_t *res =
    (trigger_t*)malloc_safe(sizeof(trigger_t));

    res->size = size;
    res->on_hit = on_hit;
    res->ndx = ~0ULL;
    return res;
}

vec_trigger_t vec_trigger_init(void)
{
    vec_trigger_t res;

    res.count = 0;
    res.allocated = 0;
    res.trigger = NULL;
    return res;
}

void vec_trigger_add(vec_trigger_t *vec, trigger_t *trigger)
{
    size_t cur = vec->count++;

    if (vec->count > vec->allocated) {
        vec->allocated += 32;
        vec->trigger = (trigger_t**)realloc(vec->trigger,
        vec->allocated * sizeof(trigger_t*));
    }
    vec->trigger[cur] = trigger;
    trigger->ndx = cur;
}

void vec_trigger_destroy(vec_trigger_t vec)
{
    free(vec.trigger);
}
