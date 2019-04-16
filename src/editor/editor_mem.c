/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static void set_texture_nearest(gluint texture)
{
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void editor_init(demo_t *demo)
{
    demo->action = ACTION_MOVE;
    demo->editor.selections = (vec_selection_t){0, 0, NULL};
    editor_load_models(demo);
    demo->editor.shader = shader_load_vert_frag(
    "src/gpu/shader/fullb_vertex.glsl", "src/gpu/shader/fullb_fragment.glsl");
    if (demo->editor.shader == 0)
        exit(84);
    demo->editor.mvp = glGetUniformLocation(demo->editor.shader, "mvp");
    set_texture_nearest(_iu.textures[IUTEX_EDITOR_GRAB]->id);
    demo->editor.grabbed = MODEL_EDITOR_MAX;
    demo->editor.grab_delta = (dvec3){0.0f, 0.0f, 0.0f};
    demo->editor.grab_first = (dvec3){0.0f, 0.0f, 0.0f};
    demo->editor.grab_now = (dvec3){0.0f, 0.0f, 0.0f};
    for (size_t i = 0; i < 3; i++)
        demo->editor.grabber_ent[i] =
        entity_create(demo->editor.model[MODEL_EDITOR_X + i]);
    demo->editor.is_wireframe = 0;
}

void editor_quit(demo_t *demo)
{
    glDeleteProgram(demo->editor.shader);
    for (size_t i = 0; i < 3; i++)
        entity_destroy(demo->editor.grabber_ent[i]);
    editor_free_models(demo);
    free(demo->editor.selections.selection);
}
