/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

void trigger_on_hit_player(entity3 *ent, entity3 *other)
{
    (void)ent;
    printf("got: %p\n", other);
}
