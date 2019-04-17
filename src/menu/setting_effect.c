/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** setting_effect
*/

#include "headers.h"

void display_x(demo_t *demo)
{
    vec2 screen = {demo->win.w , demo->win.h};
    vec2 mouse_posf = {demo->mouse.mouse_pos.x, demo->mouse.mouse_pos.y};
    vec2 relative_mouse_pos;

    relative_mouse_pos = vec2_muls(
    vec2_subs(vec2_div(mouse_posf, screen), 0.5f), 2.0f);
    relative_mouse_pos.y *= -1.0;
    printf("%f\n", relative_mouse_pos.x);
}

void move_slider(demo_t *demo, entity2_t *slider)
{
    vec2 screen = {demo->win.w , demo->win.h};
    vec2 mouse_posf = {demo->mouse.mouse_pos.x, demo->mouse.mouse_pos.y};
    vec2 relative_mouse_pos;

    relative_mouse_pos = vec2_muls(
    vec2_subs(vec2_div(mouse_posf, screen), 0.5f), 2.0f);
    relative_mouse_pos.y *= -1.0;
    //printf("%f\n", (relative_mouse_pos.x - slider->rect.p.x));
    slider->rect.p.x += (relative_mouse_pos.x - slider->rect.p.x);
}

int check_slider_side(entity2_t slider)
{
    if (slider.slider->rect.p.x <= slider.x_min)
        return 1;
    return 0;
}

void setting_buttons_effects(demo_t *demo, menu_t *menu, setting_entity_t choice)
{
    float save_x;
    display_x(demo);
    switch (choice) {
        case SETTING_RES_MINUS:
            if (menu->choosen_res > LIST_RES_1600_900) {
                menu->choosen_res--;
                menu->edited_setting = 1;
            }
            return;
        case SETTING_RES_PLUS:
            if (menu->choosen_res < LIST_RES_1920_1080) {
                menu->choosen_res++;
                menu->edited_setting = 1;
            }
            return;
        case SETTING_VOL_MASTER:
            menu->current_slider = SETTING_VOL_MASTER;
            if (!demo->mouse.button_release) {
                save_x = menu->setting[SETTING_VOL_MASTER].rect.p.x;
                move_slider(demo, menu->setting[SETTING_VOL_MASTER].slider);
                if (check_slider_side(menu->setting[SETTING_VOL_MASTER]))
                    menu->setting[SETTING_VOL_MASTER].slider->rect.p.x = save_x;
            }
            break;
        default:
            return;
    }
}

int analyse_setting_input(demo_t *demo, menu_t *menu)
{
    for (int i = 0; i < SETTING_END; i++) {
        if (check_click_pos(sfMouse_getPosition((sfWindow *)demo->win.window),
        menu->setting[i], demo->win.w, demo->win.h)) {
            setting_buttons_effects(demo, menu, SETTING_RES + i);
        }
    }
    return 1;
}
