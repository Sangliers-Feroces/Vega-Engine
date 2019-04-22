/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** vg_dialogue_display
*/

#include "headers.h"

static float get_canvas_size(rect_t target)
{
    return (target.p.x + target.s.x);
}

void vg_dialogue_draw(vg_dialogue *src)
{
    iu_entity_draw(_iu.cadre[src->cadre]);
    iu_display_str(src->texts[src->read_head].str, src->pos_size,
    src->font_index, get_canvas_size(_iu.cadre[src->cadre].rect));
    if (_demo->input.key_press[KEY_ENTER]) {
        if (src->read_head == src->nb_texts - 1) {
            _iu.current_dialogue = DIALOGUE_END;
            return;
        }
        src->read_head++;
    }
}

void vg_dialogue_quit(void)
{
    for (int i = 0; i < DIALOGUE_END; i++) {
        free(_iu.dialogue_list[i].texts);
    }
}