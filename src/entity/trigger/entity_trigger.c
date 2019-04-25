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

void vec_trigger_destroy(vec_trigger_t *vec)
{
    free(vec->trigger);
    vec->count = 0;
}

void entity3_add_trigger(entity3 *ent, dvec3 size,
void (*on_hit)(entity3 *ent, entity3 *other))
{
    trigger_t *trigger;

    if (ent->trigger != NULL) {
        printf("Error: this entity has already a trigger.\n");
        exit(84);
    }
    trigger = trigger_create(size, on_hit);
    vec_trigger_add(&_demo->world.triggers, trigger);
    ent->trigger = trigger;
}
