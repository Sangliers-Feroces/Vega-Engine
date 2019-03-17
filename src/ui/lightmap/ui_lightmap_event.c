/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** ui_lightmap_event
*/

#include "headers.h"

static void ui_lm_button_effect_ext(demo_t *demo)
{
    switch (_ui.ui_lightmap_struct.button_clicked) {
    case UILMBUTTON_START:
        compute_lightmap(demo);
        break;
    default:
        break;
    }
}

static void ui_lm_button_effect(demo_t *demo)
{
    switch (_ui.ui_lightmap_struct.button_clicked) {
    case UILMBUTTON_PLUS:
        _ui.ray_density += 10;
        break;
    case UILMBUTTON_MINUS:
        _ui.ray_density -= 10;
        if (_ui.ray_density < 10)
            _ui.ray_density = 10;
        break;
    case UILMBUTTON_BACK:
        _ui.ui_lightmap_struct.back = 1;
        break;
    case UILMBUTTON_ABORT:
        thread_abort_task();
        break;
    default:
        return ui_lm_button_effect_ext(demo);
        break;
    }
}

void ui_lm_check_click_button(demo_t *demo)
{
    _ui.ui_lightmap_struct.button_clicked = UILMBUTTON_NONE;
    for (int i = 0; i < UILMBUTTON_END; i++) {
        if (check_click_pos(demo->mouse.mouse_pos,
        _ui.ui_lightmap_struct.object[i],
        demo->win.w, demo->win.h)) {
            _ui.ui_lightmap_struct.button_clicked = UILMBUTTON_TITLE + i;
            break;
        }
    }
    ui_lm_button_effect(demo);
}

int ui_lm_poll_events(demo_t *demo)
{
    if (!poll_events(demo))
        return (0);
    if (demo->mouse.button_click & (1 << sfMouseLeft))
        ui_lm_check_click_button(demo);
    return (1);
}
