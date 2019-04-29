/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

const vec3 skybox[] = {
    {0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {1.0f, 0.0f, 0.0f},

    {1.0f, 1.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    {1.0f, 0.0f, 0.0f},

    {1.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, 1.0f},
    {0.0f, 1.0f, 1.0f},

    {0.0f, 1.0f, 1.0f},
    {1.0f, 1.0f, 1.0f},
    {1.0f, 0.0f, 1.0f},

    {0.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 1.0f},

    {0.0f, 1.0f, 1.0f},
    {0.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},

    {1.0f, 0.0f, 0.0f},
    {1.0f, 0.0f, 1.0f},
    {1.0f, 1.0f, 1.0f},

    {1.0f, 0.0f, 0.0f},
    {1.0f, 1.0f, 1.0f},
    {1.0f, 1.0f, 0.0f},

    {0.0f, 1.0f, 1.0f},
    {0.0f, 1.0f, 0.0f},
    {1.0f, 1.0f, 0.0f},

    {0.0f, 1.0f, 1.0f},
    {1.0f, 1.0f, 0.0f},
    {1.0f, 1.0f, 1.0f},

    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 1.0f},
    {1.0f, 0.0f, 0.0f},

    {1.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 1.0f},
    {1.0f, 0.0f, 1.0f}
};

static mesh_full_t* load_skybox(void)
{
    mesh_full_t *res = mesh_full_create(1, 0);

    for (size_t i = 0; i < 36 / 3; i++)
        mesh_full_add_triangle_pos(res, &skybox[i * 3]);
    return res;
}

void mesh_bank_init(void)
{
    for (size_t i = 0; i < MESH_BANK_MAX; i++)
        _demo->mesh_bank[i] = NULL;
    _demo->mesh_bank[MESH_BANK_SKYBOX] = load_skybox();
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
