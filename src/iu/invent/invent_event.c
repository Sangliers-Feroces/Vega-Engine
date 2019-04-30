/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** invent_event
*/

#include "headers.h"

static void invent_move_inventory(void)
{
    if (_demo->input.key_press[KEY_ARROW_UP]) {
        if (_iu.invent.index_cursor == 0) {
            if (_iu.invent.text_start != 0)
                _iu.invent.text_start--;
        } else
            _iu.invent.index_cursor--;
    }
    if (_demo->input.key_press[KEY_ARROW_DOWN]) {
        if (_iu.invent.index_cursor == 4) {
            if (_iu.invent.text_start != 5)
                _iu.invent.text_start++;
        } else
            _iu.invent.index_cursor++;
    }
    _iu.invent.cursor.rect.p.y = -0.25f + (_iu.invent.index_cursor * -0.08f);
    _iu.invent.focused_item = _iu.invent.text_start + _iu.invent.index_cursor;
}

int invent_poll_event(void)
{
    if (!demo_poll_events(_demo))
        return 0;
    if (_demo->input.key_press[KEY_TAB] || _demo->input.key_press[KEY_ESC])
        return 0;
    invent_move_inventory();
    return 1;
}