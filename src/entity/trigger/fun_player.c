/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

entity3* entity3_get_parent(entity3 *ent, size_t depth)
{
    entity3 *res = ent;

    for (size_t i = 0; (i < depth) && (res != NULL); i++)
        res = res->root;
    return res;
}

void make_damage_to_enemy(entity3 *ent, dvec3 dir, double hp)
{
    entity3_tag_enemy_data_t *data = ent->tag_data;

    if ((data->last_damage + 1.0) > data->t)
        return;
    ent->trans.speed = dvec3_add(ent->trans.speed, dir);
    ent->trans.speed.y += 3.0;
    data->hp -= hp;
    data->last_damage = data->t;
    if (data->hp <= 0.0)
        entity3_destroy(ent);
}

void trigger_on_hit_player(entity3 *ent, entity3 *other)
{
    entity3 *enemy = entity3_get_parent(other, 0);
    entity3_tag_player_data_t *player_data = _demo->world.player->tag_data;

    (void)ent;
    if (enemy != NULL && (enemy->tag == ENTITY3_TAG_ENEMY)) {
        if (player_data->has_atk != 1)
            return;
        make_damage_to_enemy(enemy, dvec3_add(dvec3_muls(dvec3_mul(dmat4_mul_dvec3(
        _demo->world.camera->trans.world_rot,
        dvec3_init(0.0, 0.0, 1.0)), dvec3_init(1.0, 0.0, 1.0)), 16.0),
        _demo->world.player->trans.speed),
        20.0);
    }
}
