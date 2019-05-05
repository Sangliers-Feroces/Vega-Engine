/*
** EPITECH PROJECT, 2019
** MUL_my_world_2018
** File description:
** menu_entities
*/

#include "headers.h"

/*static void setting_set_extern(menu_t *menu)
{
    menu->setting[SETTING_VOL_MASTER].slider = malloc_safe(sizeof(entity2_t));
    entity_constructor(menu->setting[SETTING_VOL_MASTER].slider,
    (entity2_param_t){
    IUTEX_SLIDER, (rect_t){{-0.278750f, 0.262f}, {0.05f, 0.05f}}, -0.999});
    menu->setting[SETTING_VOL_MASTER].x_min = -0.742500;
    menu->setting[SETTING_VOL_MASTER].x_max = -0.228750f;
}*/

static void menu_set_link_entities(menu_t *menu)
{
    entity_constructor(&menu->link[MENU_LINK_CONTINUE], (entity2_param_t){
    IUTEX_MENU_CONTINUE, (rect_t){{0.75f, -0.30f}, {0.1f, 0.1f}}, -0.999});
    entity_constructor(&menu->link[MENU_LINK_NEW], (entity2_param_t){
    IUTEX_MENU_NEW, (rect_t){{0.75f, -0.40f}, {0.1f, 0.1f}}, -0.999f});
    entity_constructor(&menu->link[MENU_LINK_SETTING], (entity2_param_t){
    IUTEX_MENU_SETTINGS, (rect_t){{0.75f, -0.50f}, {0.1f, 0.1f}}, -0.999f});
    entity_constructor(&menu->link[MENU_LINK_CREDITS], (entity2_param_t){
    IUTEX_MENU_HELP, (rect_t){{0.75f, -0.60f}, {0.1f, 0.1f}}, -0.999f});
    entity_constructor(&menu->link[MENU_LINK_QUIT], (entity2_param_t){
    IUTEX_MENU_QUIT, (rect_t){{0.75f, -0.70f}, {0.1f, 0.1f}}, -0.999f});
    entity_constructor(&menu->link[MENU_LINK_CURSOR], (entity2_param_t){
    IUTEX_MENU_CURSOR, (rect_t){{0.65f, -0.40f}, {0.1f, 0.1f}}, -0.999f});
}

void menu_set_entities(menu_t *menu)
{
    entity_constructor(&menu->background[MENU_BG_MAIN], (entity2_param_t){
    IUTEX_MENU_MAIN, (rect_t){{-1.0f, -1.0f}, {2.0f, 2.0f}}, 0.0f});
    menu_set_link_entities(menu);
    //setting_set_extern(menu);
}
