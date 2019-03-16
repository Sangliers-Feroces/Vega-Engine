/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** ui_lightmap
*/

#include "headers.h"

void ui_lightmap_set_buttons(void)
{
    _ui.ui_lightmap_struct.object[UILMBUTTON_TITLE] =
    (button_t){UIRES_LM_TITLE, (vec2){-0.30f, 0.40f}, 0.6f, -1.0f, BUTTON_REL_X};
    _ui.ui_lightmap_struct.object[UILMBUTTON_PLUS] =
    (button_t){UIRES_LM_PLUS, (vec2){0.30f, 0.0f}, 0.1f, -1.0f, BUTTON_REL_X};
    _ui.ui_lightmap_struct.object[UILMBUTTON_MINUS] =
    (button_t){UIRES_LM_MINUS, (vec2){-0.40f, 0.0f}, 0.1f, -1.0f, BUTTON_REL_X};
    _ui.ui_lightmap_struct.object[UILMBUTTON_LEGEND] =
    (button_t){UIRES_LM_LEGEND, (vec2){-0.15f, 0.20f}, 0.3f, -1.0f, BUTTON_REL_X};
    _ui.ui_lightmap_struct.object[UILMBUTTON_START] =
    (button_t){UIRES_LM_START, (vec2){-0.20f, -0.45f}, 0.4f, -1.0f, BUTTON_REL_X};
}

void ui_lightmap_display(demo_t *demo)
{
    display_nbr_array_t nbr_array =
    ui_fill_display_nbr_array(100, (vec2){0.0f, -0.50f}, 0.1f, 0.15f);

    while (poll_events(demo)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(_ui.ui_program);
        ui_lightmap_draw(nbr_array);
        sfRenderWindow_display(demo->win.window);
    }
    free(nbr_array.digits);
}