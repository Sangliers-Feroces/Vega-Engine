/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** event
*/

#include "headers.h"

static void analyse_buttons(settings_entitie_t i)
{
    switch (i) {
        case SETTINGS_VOL_MAST:
            if (!_demo->mouse.button_release)
                setting_slider_move(&_iu.settings.entities[i]);
            break;
        case SETTINGS_VOL_MUSIC:
            if (!_demo->mouse.button_release)
                setting_slider_move(&_iu.settings.entities[i]);
            break;
        case SETTINGS_VOL_SOUND:
            if (!_demo->mouse.button_release)
                setting_slider_move(&_iu.settings.entities[i]);
            break;
        default:
            return;
    }
}


static void check_buttons(void)
{
    for (int i = 0; i < SETTINGS_END; i++) {
        if (check_click_pos(_demo->mouse.mouse_pos, _iu.settings.entities[i],
        _demo->win.w, _demo->win.h))
            analyse_buttons(SETTINGS_BG + i);
    }
}

int setting_poll_event(void)
{
    if (!demo_poll_events(_demo))
        return 0;
    if (_demo->input.key_press[KEY_ESC])
        return 0;
    if (_demo->mouse.button_state)
        check_buttons();
    return 1;
}