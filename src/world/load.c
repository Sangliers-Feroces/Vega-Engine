/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static entity3* create_default_ents(void)
{
    entity3 *res = entity3_create(NULL);
    entity3 *player;
    entity3 *cam;

    player = entity3_create(res);
    player->tag = ENTITY3_TAG_PLAYER;
    player->trans.is_static = 0;
    player->trans.is_physics = 1;
    player->trans.slide_threshold = 0.8;
    player->trans.pos = dvec3_init(0.0, 64.0, 0.0);
    cam = entity3_create(player);
    cam->tag = ENTITY3_TAG_CAMERA;
    cam->trans.is_static = 0;
    cam->trans.pos = dvec3_init(0.0, 1.75, 0.0);
    entity3_add_trigger(cam, trigger_create(dvec3_init(-0.25, -0.5, 0.0),
    dvec3_init(0.25, 0.5, 3.0), TRIGGER_ON_HIT_PLAYER));
    return res;
}

static entity3* load_global_ents(void)
{
    char *path = map_get_path("ents");
    file_read_t file = file_read_create(path);
    entity3 *res;

    free(path);
    if (file.data == NULL)
        return create_default_ents();
    res = file_read_entity3(&file, NULL);
    file_read_flush(&file);
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
    ensure_path();
    _demo->world.light_dir =
    dvec3_normalize(dvec3_add(dvec3_init(-1.0, -1.0, -1.0),
    dvec3_init(0.0, 0.0, 0.2)));
    _demo->world.ents = load_global_ents();
    _demo->world.player =
    entity3_seek_tag(_demo->world.ents, ENTITY3_TAG_PLAYER);
    _demo->world.camera =
    entity3_seek_tag(_demo->world.ents, ENTITY3_TAG_CAMERA);
}
