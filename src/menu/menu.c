/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** menu
*/

#include "headers.h"

static void menu_set_object(menu_t *menu)
{
    menu->object[MENUOBJECT_ELON] =
    (button_t){UIRES_MENU_ELON, (vec2){-1.0f, -1.0f}, 1.0f, -0.999f, REL_X};
    menu->object[MENUOBJECT_INTRO] =
    (button_t){UIRES_MENU_INTRO, (vec2){-1.0f, -1.0f}, 1.0f, -0.999f, REL_X};
    menu->object[MENUOBJECT_MENU] =
    (button_t){UIRES_MENU_MENU, (vec2){0.0f, 0.0f}, 0.0f, -0.888f, REL_X};
    menu->object[MENUOBJECT_PLAY] =
    (button_t){UIRES_MENU_PLAY, (vec2){-0.85f, -0.20f}, 0.50f, -0.999f, REL_X};
    menu->object[MENUOBJECT_QUIT] =
    (button_t){UIRES_MENU_QUIT, (vec2){-0.85f, -0.45f}, 0.20f, -0.9f, REL_X};
    menu->object[MENUOBJECT_CURSOR] =
    (button_t){UIRES_MENU_CURSOR, (vec2){-0.40f, -0.37f}, 0.3f, -0.9f, REL_X};
}

int menu(demo_t *demo)
{
    menu_t menu;

    menu.intro_state = 0;
    menu.menu_state = 1;
    menu.last_return = 0;
    menu.cur_return = 0;
    menu_set_object(&menu);
    if (!menu_intro(demo, &menu))
        return 0;
    if (!menu_draw(demo, &menu))
        return 0;
    return 1;
}
