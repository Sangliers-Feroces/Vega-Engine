/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static void create_skybox(entity3 *root)
{
    entity3 *sky = entity3_create(root);

    entity3_set_render(sky, 0, mesh_full_ref_bank_init(MESH_BANK_SKYBOX),
    MATERIAL_SKYBOX);
    entity3_set_tag(sky, ENTITY3_TAG_SKYBOX);
}

static entity3* create_default_ents(void)
{
    entity3 *res = entity3_create(NULL);
    entity3 *player;
    entity3 *cam;
    entity3 *sword;

    player = entity3_create(res);
    entity3_set_tag(player, ENTITY3_TAG_PLAYER);
    player->trans.is_static = 0;
    player->trans.is_physics = 1;
    player->trans.is_collision = 1;
    player->trans.slide_threshold = 0.8;
    player->trans.pos = dvec3_init(100.0, 64.0, 100.0);
    entity3_add_trigger(player, trigger_create(dvec3_init(-0.5, 0.0,-0.5),
    dvec3_init(0.5, 1.75, 0.5), TRIGGER_ON_HIT_PLAYER));
    entity3_trans_update(player);
    cam = entity3_create(player);
    entity3_set_tag(cam, ENTITY3_TAG_CAMERA);
    cam->trans.is_static = 0;
    cam->trans.pos = dvec3_init(0.0, 1.75, 0.0);
    entity3_trans_update(cam);
    sword = entity3_create(cam);
    sword->trans.pos = dvec3_init(0.7, -0.7, 0.7);
    sword->trans.scale.x = -1.0;
    sword->trans.is_static = 0;
    entity3_trans_update(sword);
    sword = entity3_create(sword);
    sword->trans.is_static = 0;
    entity3_add_trigger(sword, trigger_create(dvec3_init(-0.5, 0.0, 0.0),
    dvec3_init(0.5, 3.0, 1.0), TRIGGER_ON_HIT_SWORD));
    entity3_set_tag(sword, ENTITY3_TAG_SWORD);
    entity3_trans_update(sword);
    create_skybox(res);
    invent_add_item(ITEM_SWORD_1);
    //invent_add_item(ITEM_SWORD_2);
    //invent_add_item(ITEM_SWORD_3);
    return res;
}

static entity3* load_global_ents(int *has_created)
{
    char *path = map_get_path("ents");
    file_read_t file = file_read_create(path);
    entity3 *res;

    free(path);
    if (file.data == NULL) {
        *has_created = 1;
        return create_default_ents();
    }
    res = file_read_entity3(&file, NULL);
    file_read_flush(&file);
    *has_created = 0;
    return res;
}

static void ensure_path(void)
{
    if (_demo->world.map_path != NULL)
        return;
    world_load_meta_map();
    world_ensure_current_map_folder();
}

void world_load_map(void)
{
    int do_respawn;

    if (_demo->world.map_path != NULL)
        return;
    ensure_path();
    invent_load();
    quest_load();
    _demo->world.tree = octree_create(NULL);
    _demo->world.light_dir =
    dvec3_normalize(dvec3_add(dvec3_init(-1.0, -1.0, -1.0),
    dvec3_init(0.0, 0.0, 0.2)));
    _demo->world.ents = load_global_ents(&do_respawn);
    _demo->world.player =
    entity3_seek_tag(_demo->world.ents, ENTITY3_TAG_PLAYER);
    _demo->world.camera =
    entity3_seek_tag(_demo->world.ents, ENTITY3_TAG_CAMERA);
    _demo->world.skybox =
    entity3_seek_tag(_demo->world.ents, ENTITY3_TAG_SKYBOX);
    if (do_respawn)
        player_respawn(_demo->world.player);
    player_update_weapon();
    vec_msg_entry_flush(&_demo->buf.msgs);
}
