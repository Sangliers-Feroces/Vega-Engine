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
    _ui.ui_lightmap_struct.object[UILMBUTTON_BACK] =
    (button_t){UIRES_LM_BACK, (vec2){0.85f, -0.90f}, 0.1f, -1.0f, BUTTON_REL_X};
    _ui.ui_lightmap_struct.object[UILMBUTTON_ABORT] =
    (button_t){UIRES_LM_ABORT, (vec2){-0.20f, -0.70f}, 0.4f, -1.0f, BUTTON_REL_X};
    _ui.ui_lightmap_struct.object[UILMBUTTON_CADRE] =
    (button_t){UIRES_CADRE, (vec2){-0.50f, 0.0f}, 0.1f, -1.0f, BUTTON_REL_X};
    _ui.ui_lightmap_struct.object[UILMBUTTON_LOADING] =
    (button_t){UIRES_RED, (vec2){-0.42f, 0.0f}, 0.1f, -0.999f, BUTTON_REL_X};
    _ui.ui_lightmap_struct.object[UILMBUTTON_POURCENT] =
    (button_t){UIRES_POURCENT, (vec2){0.12f, 0.20f}, 0.1f, -1.0f, BUTTON_REL_X};
}

static void compute_display_pourcent(display_nbr_array_t nbr_array,
size_t new_value)
{
    refresh_display_nbr_array(nbr_array, new_value);
    for (int i = 0; i < nbr_array.nb_digit; i++)
        button_draw(nbr_array.digits[i].digit);
    button_draw(_ui.ui_lightmap_struct.object[UILMBUTTON_POURCENT]);
}
void compute_lightmap(demo_t *demo)
{
    rect_t tmp_rect;
    float wololo = 0.0f;

    octree_light_rtx_noblock(demo->tree, demo->temp_ray_density);
    while (!thread_is_complete () && !_ui.ui_lightmap_struct.back
    && ui_lm_poll_events(demo)) {
        wololo = thread_get_progress();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for (int i = UILMBUTTON_ABORT; i < UILMBUTTON_END; i++) {
            tmp_rect = button_get_size(_ui.ui_lightmap_struct.object[i]);
            if (i == UILMBUTTON_LOADING) {
                tmp_rect.s.x = wololo / 1.17;
                tmp_rect.s.y = 0.135f;
            }
            else if (i == UILMBUTTON_CADRE) {
                tmp_rect.s.x = 1.0f;
                tmp_rect.s.y = 0.135f;
            }
            ui_draw_full_rel(_ui.ui_lightmap_struct.object[i].texture_index,
            tmp_rect, _ui.ui_lightmap_struct.object[i].depth);
        }
        compute_display_pourcent(_ui.loading_pourcent, (size_t)(wololo * 100));
        sfRenderWindow_display(demo->win.window);
    }
    thread_wait();
    _ui.ui_lightmap_struct.back = 0;
    texture2f_refresh_gpu(_lightmaps.base);
    demo->cam.aperture = (octree_get_max_lumel(demo->tree) / 3.0f) / 2.0f;
}

void ui_lightmap_display(demo_t *demo)
{
    _ui.ui_lightmap_struct.back = 0;

    while (ui_lm_poll_events(demo) && !_ui.ui_lightmap_struct.back) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(_ui.ui_program);
        refresh_display_nbr_array(_ui.display_nbr_array, demo->temp_ray_density);
        ui_lightmap_draw();
        sfRenderWindow_display(demo->win.window);
    }
}
