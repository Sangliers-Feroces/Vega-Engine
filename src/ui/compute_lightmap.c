/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** compute_lightmap
*/

#include "headers.h"

static void compute_display_pourcent(display_nbr_array_t nbr_array,
size_t new_value)
{
    refresh_display_nbr_array(nbr_array, new_value);
    for (int i = 0; i < nbr_array.nb_digit; i++)
        button_draw(nbr_array.digits[i].digit);
    button_draw(_ui.ui_lightmap_struct.object[UILMBUTTON_POURCENT]);
}

static void draw_thread_progress(float thread_progress)
{
    rect_t tmp_rect;

    for (int i = UILMBUTTON_ABORT; i < UILMBUTTON_END; i++) {
        tmp_rect = button_get_size(_ui.ui_lightmap_struct.object[i]);
        if (i == UILMBUTTON_LOADING) {
            tmp_rect.s.x = thread_progress / 1.17;
            tmp_rect.s.y = 0.135f;
        }
        else if (i == UILMBUTTON_CADRE) {
            tmp_rect.s.x = 1.0f;
            tmp_rect.s.y = 0.135f;
        }
        ui_draw_full_rel(_ui.ui_lightmap_struct.object[i].texture_index,
        tmp_rect, _ui.ui_lightmap_struct.object[i].depth);
    }
}

void compute_lightmap(demo_t *demo)
{
    float thread_progress;

    octree_light_rtx_noblock(demo->tree, _ui.ray_density);
    while (!thread_is_complete () && !_ui.ui_lightmap_struct.back
    && ui_lm_poll_events(demo)) {
        thread_progress = thread_get_progress();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        draw_thread_progress(thread_progress);
        compute_display_pourcent(_ui.loading_pourcent,
        (size_t)(thread_progress * 100));
        sfRenderWindow_display(demo->win.window);
    }
    thread_wait();
    _ui.ui_lightmap_struct.back = 0;
    texture2f_refresh_gpu(_lightmaps.base);
    demo->cam.aperture = (octree_get_max_lumel(demo->tree) / 3.0f) / 2.0f;
}
