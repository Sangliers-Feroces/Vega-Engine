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
    player->trans.pos = dvec3_init(0.0, 64.0, 0.0);
    cam = entity3_create(player);
    cam->tag = ENTITY3_TAG_CAMERA;
    cam->trans.is_static = 0;
    cam->trans.pos = dvec3_init(0.0, 1.75, 0.0);
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

static void unload_global_ents(void)
{
    char *path = map_get_path("ents");
    file_write_t file = file_write_create();

    file_write_entity3(&file, _demo->world.ents);
    file_write_flush(&file, path);
    free(path);
    entity3_destroy(_demo->world.ents);
}

static void create_folder(const char *path)
{
    if (mkdir(path, 0755) < 0) {
        printf("Error: can't create '%s' folder.\n", path);
        exit(84);
    }
}

static void create_meta(void)
{
    const char *path = "maps/meta";
    file_write_t file_w;

    file_w = file_write_create();
    file_write_string(&file_w, "maps/world");
    file_write_flush(&file_w, path);
}

void ensure_folder_maps(void)
{
    FILE *folder = fopen("maps", "rb");

    if (folder == NULL)
        create_folder("maps");
    else
        fclose(folder);
}

static void load_meta_map(void)
{
    const char *path = "maps/meta";
    file_read_t file;

    file = file_read_create(path);
    if (file.data == NULL) {
        create_meta();
        file = file_read_create(path);
    }
    if (file.data == NULL) {
        ensure_folder_maps();
        create_meta();
        file = file_read_create(path);
    }
    if (file.data == NULL) {
        printf("Error: can't access to maps/meta.\n");
        exit(84);
    }
    _demo->world.map_path = file_read_string(&file);
    file_read_flush(&file);
}

void world_ensure_current_map_folder(void)
{
    FILE *folder = fopen("maps", "rb");
    char *map_folder_path;

    map_folder_path = _demo->world.map_path;
    folder = fopen(map_folder_path, "rb");
    if (folder == NULL)
        create_folder(map_folder_path);
    else
        fclose(folder);
}

static void ensure_path(void)
{
    if (_demo->world.map_path != NULL)
        return;
    load_meta_map();
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

void world_unload_map(void)
{
    printf("Saving world at '%s'.. Please wait.\n", _demo->world.map_path);
    unload_global_ents();
    while (_demo->world.chunk_count > 0)
        chunk_destroy(_demo->world.chunk[0]);
    octree_destroy(&_demo->world.tree);
    vec_trigger_destroy(&_demo->world.triggers);
    printf("Done.\n");
}

void world_init(demo_t *demo)
{
    demo->world.map_path = NULL;
    demo->world.chunk_count = 0;
    demo->world.chunk_allocated = 0;
    demo->world.chunk = NULL;
    demo->world.triggers = vec_trigger_init();
    demo->world.chunk2d_area = (srect){{0, 0}, {1, 1}};
    demo->world.chunk2d = (chunk_t**)malloc_safe(sizeof(chunk_t*));
    demo->world.chunk2d[0] = NULL;
    demo->world.tree = octree_create(NULL);
    entity3_update_tag_init();
    world_trigger_init();
}

void world_quit(demo_t *demo)
{
    world_unload_map();
    free(demo->world.chunk);
    free(demo->world.chunk2d);
    free(demo->world.map_path);
}
