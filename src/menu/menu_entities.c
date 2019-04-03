/*
** EPITECH PROJECT, 2019
** MUL_my_world_2018
** File description:
** menu_entities
*/

#include "headers.h"

static void menu_set_link_entities(menu_t *menu)
{
    menu->link[MENU_LINK_CONTINUE] = (entity2_t){IUTEX_MENU_CONTINUE,
    (rect_t){{0.75f, -0.30f}, {0.1f, 0.1f}}, -0.999f, IUREL_FULL};
    menu->link[MENU_LINK_NEW] = (entity2_t){IUTEX_MENU_NEW,
    (rect_t){{0.75f, -0.40f}, {0.1f, 0.1f}}, -0.999f, IUREL_FULL};
    menu->link[MENU_LINK_LOAD] = (entity2_t){IUTEX_MENU_LOAD,
    (rect_t){{0.75f, -0.50f}, {0.1f, 0.1f}}, -0.999f, IUREL_FULL};
    menu->link[MENU_LINK_SETTING] = (entity2_t){IUTEX_MENU_SETTINGS,
    (rect_t){{0.75f, -0.60f}, {0.1f, 0.1f}}, -0.999f, IUREL_FULL};
    menu->link[MENU_LINK_CREDITS] = (entity2_t){IUTEX_MENU_CREDITS,
    (rect_t){{0.75f, -0.70f}, {0.1f, 0.1f}}, -0.999f, IUREL_FULL};
    menu->link[MENU_LINK_QUIT] = (entity2_t){IUTEX_MENU_QUIT,
    (rect_t){{0.75f, -0.80f}, {0.1f, 0.1f}}, -0.999f, IUREL_FULL};
    menu->link[MENU_LINK_CURSOR] = (entity2_t){IUTEX_MENU_CURSOR,
    (rect_t){{0.65f, -0.40f}, {0.1f, 0.1f}}, -0.999f, IUREL_FULL};
}

void menu_set_entities(menu_t *menu)
{
    menu->background[MENU_BG_MAIN] =
    (entity2_t){IUTEX_MENU_MAIN, (rect_t){{-1.0f, -1.0f}, {2.0f, 2.0f}},
    -0.888f, IUREL_FULL};
    menu_set_link_entities(menu);
}