/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** menu
*/

#include "headers.h"

static const ui_texture_descriptor_t texture_desc_array[] = {
    {MENURES_ELON, "res/ui/menu/elon.jpg"},
    {MENURES_INTRO, "res/ui/menu/menu_intro.png"},
    {MENURES_MENU, "res/ui/menu/menu.png"},
    {MENURES_PLAY, "res/ui/menu/menu_play.png"},
    {MENURES_QUIT, "res/ui/menu/menu_quit.png"},
    {MENUOBJECT_CURSOR, "res/ui/menu/cursor.png"},
    {0, NULL}
};

static void menu_load_textures(menu_t *menu,
const ui_texture_descriptor_t descriptors_array[])
{
    for (int i = 0; descriptors_array[i].path != NULL; i++)
        menu->textures[descriptors_array[i].index] =
        texture2_load(descriptors_array[i].path);
}

static void menu_set_texture_to_null(menu_t *menu)
{
    for (int i = 0; i < MENURES_MAX; i++)
        menu->textures[i] = NULL;
}

static void menu_set_object(menu_t *menu)
{
    menu->object[MENUOBJECT_ELON] =
    (button_t){MENURES_ELON, (vec2){-1.0f, -1.0f}, 1.0f, -0.999f, REL_X};
    menu->object[MENUOBJECT_INTRO] =
    (button_t){MENURES_INTRO, (vec2){-1.0f, -1.0f}, 1.0f, -0.999f, REL_X};
    menu->object[MENUOBJECT_MENU] =
    (button_t){MENURES_MENU, (vec2){0.0f, 0.0f}, 0.0f, -0.888f, REL_X};
    menu->object[MENUOBJECT_PLAY] =
    (button_t){MENURES_PLAY, (vec2){-0.80f, -0.50f}, 0.5f, -0.999f, REL_X};
    menu->object[MENUOBJECT_QUIT] =
    (button_t){MENURES_QUIT, (vec2){-1.0f, -0.80f}, 0.5f, -0.9f, REL_X};
    menu->object[MENUOBJECT_CURSOR] =
    (button_t){MENURES_CURSOR, (vec2){-0.40f, -0.37f}, 0.3f, -0.9f, REL_X};
}

int menu(demo_t *demo)
{
    menu_t menu;

    menu.intro_state = 0;
    menu.menu_state = 0;
    menu_set_texture_to_null(&menu);
    menu_load_textures(&menu, texture_desc_array);
    menu_set_object(&menu);
    if (!menu_intro(demo, &menu))
        return 0;
    if (!menu_draw(demo, &menu))
        return 0;
    return 1;
}