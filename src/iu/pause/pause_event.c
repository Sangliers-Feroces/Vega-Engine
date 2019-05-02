/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** pause_event
*/

#include "headers.h"

static void refresh_str_scaling(void)
{
    _iu.pause.buttons[_iu.pause.state].rect.s =
    vec2_muls(_iu.pause.buttons[_iu.pause.state].rect.s, 1.2f);
    _iu.pause.buttons[_iu.pause.state].rect.p =
    vec2_subs(_iu.pause.buttons[_iu.pause.state].rect.p, 0.02f);
    if (_iu.pause.last_state && _iu.pause.last_state != _iu.pause.state) {
        _iu.pause.buttons[_iu.pause.last_state].rect.s =
        vec2_divs(_iu.pause.buttons[_iu.pause.last_state].rect.s, 1.2f);
        _iu.pause.buttons[_iu.pause.last_state].rect.p =
        vec2_adds(_iu.pause.buttons[_iu.pause.last_state].rect.p, 0.02f);
    }
    _iu.pause.last_state = _iu.pause.state;
}

int iu_pause_poll_event(void)
{
    if (!demo_poll_events(_demo))
        return 0;
    if (_demo->input.key_press[KEY_ESC] || _demo->input.key_press[KEY_ENTER])
        return 0;
    if (_demo->input.key_press[KEY_ARROW_DOWN] && _iu.pause.state < 4) {
        _iu.pause.state++;
        refresh_str_scaling();
    }
    if (_demo->input.key_press[KEY_ARROW_UP] && _iu.pause.state > 1) {
        _iu.pause.state--;
        refresh_str_scaling();
    }
    return 1;
}