/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** setting_effect
*/

#include "headers.h"

void display_x(demo_t *demo)//c'est pour le debug
{
    vec2 screen = {demo->win.w , demo->win.h};
    vec2 mouse_posf = {demo->mouse.mouse_pos.x, demo->mouse.mouse_pos.y};
    vec2 relative_mouse_pos;

    relative_mouse_pos = vec2_muls(
    vec2_subs(vec2_div(mouse_posf, screen), 0.5f), 2.0f);
    relative_mouse_pos.y *= -1.0;
    //printf("x : %f || y : %f\n", relative_mouse_pos.x, relative_mouse_pos.y);
}

void setting_buttons_effects(demo_t *demo, menu_t *menu,
setting_entity_t choice)
{
    //display_x(demo);
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
            if (!demo->mouse.button_release)
                sfMusic_setVolume(menu->music, menu_slider_move(demo, &menu->setting[SETTING_VOL_MASTER]) * 100);
            break;
        default:
            return;
    }
}