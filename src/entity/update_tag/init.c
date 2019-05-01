/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static const entity3_tag_update_desc_t desc[] = {
    {ENTITY3_TAG_PLAYER, &entity3_tag_update_player,
    sizeof(entity3_tag_player_data_t), &entity3_tag_init_player},
    {ENTITY3_TAG_NONE, NULL, 0, NULL}
};

void entity3_update_tag_init(void)
{
    for (size_t i = 0; i < ENTITY3_TAG_MAX; i++)
        _demo->world.tag[i] = (entity3_tag_meta_t){NULL, 0, NULL};
    for (size_t i = 0; desc[i].tag != ENTITY3_TAG_NONE; i++)
        _demo->world.tag[desc[i].tag] =
        (entity3_tag_meta_t){desc[i].fun, desc[i].data_size, desc[i].data_init};
}
