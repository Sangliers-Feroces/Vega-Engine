/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

void entity3_trans_update(entity3 *ent)
{
    if (!(dvec3_eq(ent->trans.pos, ent->trans.pos_on_model) &&
    dvec3_eq(ent->trans.rot, ent->trans.rot_on_model) &&
    dvec3_eq(ent->trans.scale, ent->trans.scale_on_model))) {
        dmat4_model(&ent->trans, ent->trans.model, ent->trans.model_rot);
        ent->trans.pos_on_model = ent->trans.pos;
        ent->trans.rot_on_model = ent->trans.rot;
        ent->trans.scale_on_model = ent->trans.scale;
    }
    if (ent->root != NULL) {
        dmat4_mul(ent->root->trans.world, ent->trans.model, ent->trans.world);
        dmat4_mul(ent->root->trans.world_rot, ent->trans.model_rot,
        ent->trans.world_rot);
    }
    else {
        dmat4_copy(ent->trans.model, ent->trans.world);
        dmat4_copy(ent->trans.model_rot, ent->trans.world_rot);
    }
}

void entity3_update_solo(entity3 *ent)
{
    ent->trans.t += _demo->win.framelen;
    if (_demo->world.tag[ent->tag].update != NULL)
        _demo->world.tag[ent->tag].update(ent);
    if (!ent->trans.is_static) {
        if (ent->trans.is_physics)
            entity3_physics(ent);
        entity3_trans_update(ent);
    }
    if (ent->trigger != NULL)
        trigger_update(ent->trigger);
}

static void loot_enemy(entity3 *ent)
{
    entity3_tag_player_data_t *data = _demo->world.player->tag_data;
    entity3_tag_enemy_data_t *enemy_data = ent->tag_data;

    if (enemy_data->enemy_type == ENEMY_FISH)
        data->xp += 2;
    else
        data->xp++;
    if (data->xp >= data->max_xp) {
        data->max_hp *= 1.1;
        data->hp = data->max_hp;
        data->xp = 0.0;
        data->max_xp *= 1.1;
        data->level++;
        data->max_mana += 0.4;
    }
    if ((rand() % 3) == 0)
        invent_add_item(ITEM_APPLE);
}

static void kill_ent(entity3 *ent)
{
    if (ent->tag == ENTITY3_TAG_ENEMY)
        loot_enemy(ent);
    entity3_destroy(ent);
}

void entity3_update(entity3 *ent)
{
    if (ent->trans.t > ent->trans.life) {
        if (ent->tag == ENTITY3_TAG_PLAYER)
            return player_respawn(ent);
        kill_ent(ent);
        return;
    }
    entity3_update_solo(ent);
    for (size_t i = 0; i < ent->sub.count; i++)
        entity3_update(ent->sub.ent[i]);
}
