/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** ui_buttons
*/

#include "headers.h"

void ui_swicth_button_action(demo_t *demo)
{
    switch (_ui.button_clicked) {
    case UIBUTTON_MOVE:
        printf("Move\n");
        break;
    case UIBUTTON_PAINT:
        printf("Paint\n");
        break;
    case UIBUTTON_TEXTURE: // a separer dans une fonction a part
        _ui.selected_texture++;
        if (_ui.selected_texture == demo->texture_panel.count)
            _ui.selected_texture = 0;
        break;
    case UIBUTTON_LIGHTMAPS:
        printf("Lightmap\n");
        break;
    case UIBUTTON_PLAY:
        printf("Play\n");
        break;
    case UIBUTTON_ISO:
        printf("Iso\n");
        break;
    case UIBUTTON_CAM:
        printf("Cam\n");
        break;
    default:
        return;
    }
    _ui.button_clicked = UINOBUTTON;
}

static int check_click_pos(sfVector2i mouse_pos, button_t button,
float width_screen, float height)
{
    vec2 screen = {width_screen, height};
    vec2 mouse_posf = {mouse_pos.x, mouse_pos.y};
    vec2 relative_mouse_pos;

    relative_mouse_pos = vec2_muls(
    vec2_subs(vec2_div(mouse_posf, screen), 0.5f), 2.0f);
    relative_mouse_pos.y *= -1.0;
    return rect_is_vec2_inside(button_get_size(button), relative_mouse_pos);
}

void ui_check_click_button(demo_t *demo)
{
    _ui.button_clicked = UINOBUTTON;
    for (int i = 0; i < UIBUTTON_MAX; i++) {
        if (check_click_pos(demo->mouse.mouse_pos, _ui.buttons[i],
        demo->win.w, demo->win.h)) {
            _ui.button_clicked = UIBUTTON_MOVE + i;
        }
    }
    ui_button_effect(demo);
}
