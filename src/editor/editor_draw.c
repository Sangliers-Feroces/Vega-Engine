/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static void update_grab_pos(demo_t *demo)
{
    vec3 acc = (vec3){0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < demo->editor.selections.count; i++)
        acc = vec3_add(acc, demo->editor.selections.selection[i]);
    demo->editor.grab = vec3_divs(acc, (float)demo->editor.selections.count);
}

static void draw_grab(demo_t *demo)
{
    entity_t entity;
    float scale = 2.0f;

    if (demo->editor.selections.count == 0)
        return;
    update_grab_pos(demo);
    entity.model = demo->editor.model[MODEL_EDITOR_X];
    entity.scale = (vec3){scale, scale, scale};
    entity.rot = (vec3){0.0f, 0.0f, 0.0f};
    entity.pos = demo->editor.grab;
    entity_draw(demo, &entity);
}

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
    draw_grab(demo);
}
