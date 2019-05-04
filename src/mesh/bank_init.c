/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static const mesh_desc_t desc[] = {
    {MESH_BANK_SWORD, "res/model/veget/arm_sword.obj"},
    {MESH_BANK_ENEMY1, "res/model/veget/casa_2.obj"},
    {MESH_BANK_CASA_L0, "res/model/veget/casa_1.obj"},
    {MESH_BANK_CASA_L1, "res/model/veget/casa_1.obj"},
    {MESH_BANK_CASA_L2, "res/model/veget/casa_1.obj"},
    {MESH_BANK_KNIGHT, "res/model/veget/Knight.obj"},
    {MESH_BANK_MAX, NULL}
};

const vec3 skybox[] = {
    {-10.0f, -10.0f, 1.0f},
    {-10.0f, 10.0f, 1.0f},
    {10.0f, -10.0f, 1.0f},
    {-10.0f, 10.0f, 1.0f},
    {10.0f, 10.0f, 1.0f},
    {10.0f, -10.0f, 1.0f}
};

static mesh_full_t* load_skybox(void)
{
    mesh_full_t *res = mesh_full_create(1, 0);

    for (size_t i = 0; i < 6 / 3; i++)
        mesh_full_add_triangle_pos(res, &skybox[i * 3]);
    return res;
}

static mesh_full_t* load_particle1(void)
{
    mesh_full_t *res = mesh_full_create(1, 0);
    vec3 p[3] = {{0.0, 0.0, 0.0}, {0.0, 0.3, 0.0}, {0.3, 0.0, 0.0}};

    mesh_full_add_quad(res, p);
    return res;
}

static mesh_full_t* load_grass(void)
{
    mesh_full_t *res = mesh_full_create(1, 0);
    vec3 p_a[3];
    vec3 a;
    vec3 b;

    for (size_t i = 0; i < 32; i++) {
        a.x = (randf() - 0.5) * 2.0;
        a.y = 0.0f;
        a.z = (randf() - 0.5) * 2.0;
        b.x = (randf() - 0.5) * 2.0;
        b.y = 0.0f;
        b.z = (randf() - 0.5) * 2.0;
        p_a[0] = a;
        p_a[2] = vec3_add(a, vec3_normalize(vec3_sub(a, b)));
        p_a[1] = a;
        p_a[1].y = 0.75f;
        p_a[1].y += randf() * 0.5;
        mesh_full_add_quad(res, p_a);
    }
    return res;
}

void mesh_bank_init(void)
{
    for (size_t i = 0; i < MESH_BANK_MAX; i++)
        _demo->mesh_bank[i] = NULL;
    _demo->mesh_bank[MESH_BANK_SKYBOX] = load_skybox();
    _demo->mesh_bank[MESH_BANK_GRASS1] = load_grass();
    _demo->mesh_bank[MESH_BANK_PARTICLE1] = load_particle1();
    for (size_t i = 0; desc[i].bank != MESH_BANK_MAX; i++)
        _demo->mesh_bank[desc[i].bank] = mesh_load_obj(desc[i].path);
    for (size_t i = 0; i < MESH_BANK_MAX; i++)
        if (_demo->mesh_bank[i] == NULL) {
            printf("Can't load mesh #%zu\n", i);
            exit(84);
        }
}

void mesh_bank_quit(void)
{
    for (size_t i = 0; i < MESH_BANK_MAX; i++)
        mesh_full_destroy(_demo->mesh_bank[i]);
}
