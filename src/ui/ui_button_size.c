/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** ui
*/

#include "headers.h"

static rect_t get_x_size(button_t button)
{
    vec2 size_ac = _ui.textures[button.texture_index]->size;
    float ratio = _ui.textures[button.texture_index]->size.x /
    _ui.textures[button.texture_index]->size.y;

    size_ac = vec2_divs(size_ac, _ui.textures[button.texture_index]->size.y);
    size_ac.x /= ratio;
    size_ac.y *= _ui.ratiowh / ratio;
    return (rect_t){button.pos, vec2_muls(size_ac, button.size)};
}

static rect_t get_y_size(button_t button)
{
    vec2 size_ac = _ui.textures[button.texture_index]->size;

    size_ac = vec2_divs(size_ac, _ui.textures[button.texture_index]->size.y);
    size_ac.x /= _ui.ratiowh;
    return (rect_t){button.pos, vec2_muls(size_ac, button.size)};
}

rect_t button_get_size(button_t button)
{
    if (button.rel == BUTTON_REL_X)
        return get_x_size(button);
    else
        return get_y_size(button);
}
