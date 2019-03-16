/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

void editor_draw(demo_t *demo)
{
    entity_t entity;
    float scale = 0.5f;
    float scaleh = scale / 2.0f;

    entity.model = demo->editor.model[MODEL_EDITOR_SELECT];
    entity.scale = (vec3){scale, scale, scale};
    entity.rot = (vec3){0.0f, 0.0f, 0.0f};
    for (size_t i = 0; i < demo->editor.selections.count; i++) {
        entity.pos = demo->editor.selections.selection[i];
        entity.pos = vec3_sub(entity.pos, (vec3){scaleh, scaleh, scaleh});
        entity_draw(demo, &entity);
    }
}
