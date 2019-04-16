/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static void update_grab_pos(demo_t *demo)
{
    dvec3 acc = (dvec3){0.0, 0.0, 0.0};

    for (size_t i = 0; i < demo->editor.selections.count; i++)
        acc = dvec3_add(acc, demo->editor.selections.selection[i]);
    demo->editor.grab = dvec3_divs(acc, (float)demo->editor.selections.count);
    demo->editor.grab =
    dvec3_add(dvec3_adds(demo->editor.grab, 0.02), demo->editor.grab_delta);
}

static void draw_grab(demo_t *demo)
{
    entity_t *entity;
    double scale = 3.0;

    if (demo->editor.selections.count == 0)
        return;
    update_grab_pos(demo);
    for (size_t i = 0; i < 3; i++) {
        entity_refresh(demo->editor.grabber_ent[i]);
        entity = demo->editor.grabber_ent[i];
        entity->scale = (dvec3){scale, scale, scale};
        entity->pos = demo->editor.grab;
        entity_draw(demo, entity);
    }
}

void editor_draw(demo_t *demo)
{
    entity_t entity;
    double scale = 0.25;
    double scaleh = scale / 2.0;

    glDisable(GL_CULL_FACE);
    entity.model = demo->editor.model[MODEL_EDITOR_SELECT];
    entity.scale = (dvec3){scale, scale, scale};
    entity.rot = (dvec3){0.0, 0.0, 0.0};
    for (size_t i = 0; i < demo->editor.selections.count; i++) {
        entity.pos = demo->editor.selections.selection[i];
        entity.pos = dvec3_sub(entity.pos, (dvec3){scaleh, scaleh, scaleh});
        entity_draw(demo, &entity);
    }
    draw_grab(demo);
    glEnable(GL_CULL_FACE);
}
