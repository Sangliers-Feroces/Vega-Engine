/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

const vertex_t model_select[] =
{{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
{{0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
{{1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
{{0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
{{1.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
{{1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
{{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
{{1.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
{{0.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
{{1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
{{0.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
{{1.0f, 0.0f, 1.0f}, {1.0f, 0.0f}}};

void editor_load_models(demo_t *demo)
{
    demo->editor.model[MODEL_EDITOR_SELECT] =
    model_create(model_select, 12, _ui.textures[UIRES_EDITOR_SELECT]);
}

void editor_free_models(demo_t *demo)
{
    for (size_t i = 0; i < MODEL_EDITOR_MAX; i++)
        model_destroy(demo->editor.model[i]);
}
