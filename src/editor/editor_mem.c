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
    demo->editor.selections = (vec_selection_t){0, 0, NULL};
    editor_load_models(demo);
    demo->editor.shader = shader_load_vert_frag(
    "src/gpu/shader/fullb_vertex.glsl", "src/gpu/shader/fullb_fragment.glsl");
    if (demo->editor.shader == 0)
        exit(84);
    demo->editor.mvp = glGetUniformLocation(demo->editor.shader, "mvp");
    set_texture_nearest(_ui.textures[UIRES_EDITOR_GRAB]->id);
}

void editor_quit(demo_t *demo)
{
    glDeleteProgram(demo->editor.shader);
    editor_free_models(demo);
    free(demo->editor.selections.selection);
}
