/*
** EPITECH PROJECT, 2019
** my_wrodl
** File description:
** menu_buttons
*/

#include "headers.h"

void menu_set_object(menu_t *menu)
{
    menu->object[MENUOBJECT_ELON] =
    (button_t){UIRES_MENU_ELON, (vec2){-1.0f, -1.0f}, 1.0f, -0.999f, REL_X};
    menu->object[MENUOBJECT_INTRO] =
    (button_t){UIRES_MENU_INTRO, (vec2){-1.0f, -1.0f}, 1.0f, -0.999f, REL_X};
    menu->object[MENUOBJECT_DEV] =
    (button_t){UIRES_MENU_DEV, (vec2){-1.0f, -1.0f}, 1.0f, -0.999f, REL_X};
    menu->object[MENUOBJECT_ENGINE] =
    (button_t){UIRES_MENU_ENGINE, (vec2){-1.0f, -1.0f}, 1.0f, -0.999f, REL_X};
    menu->object[MENUOBJECT_MENU] =
    (button_t){UIRES_MENU_MENU, (vec2){0.0f, 0.0f}, 0.0f, -0.888f, REL_X};
    menu->object[MENUOBJECT_PLAY] =
    (button_t){UIRES_MENU_PLAY, (vec2){-0.85f, -0.20f}, 0.50f, -0.999f, REL_X};
    menu->object[MENUOBJECT_QUIT] =
    (button_t){UIRES_MENU_QUIT, (vec2){-0.85f, -0.40f}, 0.20f, -0.9f, REL_X};
    menu->object[MENUOBJECT_CURSOR] =
    (button_t){UIRES_MENU_CURSOR, (vec2){-0.30f, -0.22f}, 0.1f, -0.9f, REL_X};
}