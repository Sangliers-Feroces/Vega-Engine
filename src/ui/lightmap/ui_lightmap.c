/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** ui_lightmap
*/

#include "headers.h"

static const ui_lm_tex_desc_t texture_desc_array[] = {
    {UILIGHTMAP_BG, "res/ui/lightmap_menu/ui_lightmap_bg.png"},
    {0, NULL}
};

void ui_lightmap_display(demo_t *demo)
{
    while (poll_events(demo)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(_ui.ui_program);
        ui_lightmap_draw_background(_ui.ui_lightmap_struct.object);
        sfRenderWindow_display(demo->win.window);
    }
}

ui_lm_struct_t ui_lm_init(demo_t *demo)
{
    ui_lm_struct_t ui_lm_struct;

    ui_lm_set_texture_array(&ui_lm_struct, texture_desc_array);
    ui_lm_struct.object = (button_t)
    {UILIGHTMAP_BG, (vec2){-0.95f, 0.70f}, 1.0f, -0.999f, BUTTON_REL_X};
    return ui_lm_struct;
}