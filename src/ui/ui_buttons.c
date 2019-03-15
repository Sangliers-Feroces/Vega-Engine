/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** ui_buttons
*/

#include "headers.h"

void ui_swicth_button_action(void)
{
    switch (_ui.button_clicked) {
    case UIBUTTON_MOVE:
        return (void)printf("Move\n");
    case UIBUTTON_PAINT:
        return (void)printf("Paint\n");
    case UIBUTTON_TEXTURE:
        return (void)printf("Texture\n");
    case UIBUTTON_LIGHTMAPS:
        return (void)printf("Lightmap\n");
    case UIBUTTON_PLAY:
        return (void)printf("Play\n");
    case UIBUTTON_ISO:
        return (void)printf("Iso\n");
    case UIBUTTON_CAM:
        return (void)printf("Cam\n");
    default:
        return;
    }
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
