/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** ui_buttons
*/

#include "headers.h"

void ui_swicth_button_action(void)
{
    switch (_ui.button_clicked)
    {
        case UIBUTTON_MOVE:
            printf("Move\n");
            break;
        case UIBUTTON_PAINT:
            printf("Paint\n");
            break;
        case UIBUTTON_TEXTURE:
            printf("Texture\n");
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
        default:
            break;
    }
    _ui.button_clicked = UINOBUTTON;
}

static int check_click_pos(sfVector2i mouse_pos, button_t button, float width_screen, float height)
{
    vec2 screen = {width_screen, height};
    vec2 mouse_posf = {mouse_pos.x, mouse_pos.y};
    vec2 relative_mouse_pos;
    

    relative_mouse_pos = vec2_muls(vec2_subs(vec2_div(mouse_posf, screen), 0.5f), 2.0f);
    if (is_vec2_inside_rect(relative_mouse_pos, button_get_size(button))) {
        return 1;
    }
    return 0;
}

void ui_check_click_button(demo_t *demo)
{
    for (int i = 0; i < UIBUTTON_MAX; i++) {
        if (check_click_pos(demo->mouse.mouse_pos, _ui.buttons[i], demo->win.w, demo->win.h)) {
            _ui.button_clicked = UIBUTTON_MOVE + i;
            return;
        }
    }
    _ui.button_clicked = UINOBUTTON;
}