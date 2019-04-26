/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static const entity3_tag_update_desc_t desc[] = {
    {ENTITY3_TAG_PLAYER, &entity3_tag_update_player},
    {ENTITY3_TAG_NONE, NULL}
};

void entity3_update_tag_init(void)
{
    for (size_t i = 0; i < ENTITY3_TAG_MAX; i++)
        _demo->world.tag_update[i] = NULL;
    for (size_t i = 0; desc[i].tag != ENTITY3_TAG_NONE; i++)
        _demo->world.tag_update[desc[i].tag] = desc[i].fun;
}
