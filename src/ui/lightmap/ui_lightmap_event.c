/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** ui_lightmap_event
*/

#include "headers.h"

static int do_stuff_event(demo_t *demo, sfEvent event)
{
    switch (event.type) {
    case sfEvtClosed:
        sfRenderWindow_close(demo->win.window);
        return (0);
    case sfEvtMouseButtonPressed:
        demo->mouse.button_state |= (1 << event.mouseButton.button);
        break;
    case sfEvtMouseButtonReleased:
        demo->mouse.button_state &= ~(1 << event.mouseButton.button);
        break;
    default:
        break;
    }
    return (1);
}

static void poll_click(demo_t *demo)
{
    demo->mouse.button_click = 0;
    for (size_t i = 0; i < 16; i++)
        demo->mouse.button_click |=
        ((((demo->mouse.button_state >> i) & 1) == 0) &&
        (((demo->mouse.button_last >> i) & 1) == 1)) << i;
}

static void ui_lm_button_effect(demo_t *demo)
{
    if (_ui.ui_lightmap_struct.button_clicked == UILMBUTTON_PLUS)
        demo->temp_ray_density += 10;
    if (_ui.ui_lightmap_struct.button_clicked == UILMBUTTON_MINUS
    && demo->temp_ray_density > 10)
        demo->temp_ray_density -= 10;
}

void ui_lm_check_click_button(demo_t *demo)
{
    _ui.ui_lightmap_struct.button_clicked = UILMBUTTON_NONE;
    for (int i = 0; i < UILMBUTTON_END; i++) {
        if (check_click_pos(demo->mouse.mouse_pos,
        _ui.ui_lightmap_struct.object[i],
        demo->win.w, demo->win.h)) {
            _ui.ui_lightmap_struct.button_clicked = UILMBUTTON_TITLE + i;
        }
    }
    ui_lm_button_effect(demo);
}

int ui_lm_poll_events(demo_t *demo)
{
    sfEvent event;

    demo->mouse.button_last = demo->mouse.button_state;
    demo->mouse.last_pos = demo->mouse.mouse_pos;
    demo->mouse.mouse_pos = sfMouse_getPositionRenderWindow(demo->win.window);
    if (!sfRenderWindow_isOpen(demo->win.window))
        return (0);
    while (sfRenderWindow_pollEvent(demo->win.window, &event))
        if (!do_stuff_event(demo, event))
            return (0);
    poll_click(demo);
    if (demo->mouse.button_click & (1 << sfMouseLeft))
        ui_lm_check_click_button(demo);
    return (1);
}