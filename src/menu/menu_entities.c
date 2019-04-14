/*
** EPITECH PROJECT, 2019
** MUL_my_world_2018
** File description:
** menu_entities
*/

#include "headers.h"

static void setting_set_entities(menu_t *menu)
{
    entity_constructor(&menu->setting[SETTING_RES], (entity2_param_t){
    IUTEX_SETTING_RES, (rect_t){{-0.80f, 0.50f},{0.15f, 0.1f}}, -0.999});
    entity_constructor(&menu->setting[SETTING_RES_CHOICE], (entity2_param_t){
    IUTEX_SETTING_RES_1600_900, (rect_t){{-0.50f, 0.50f},{0.15f, 0.1f}}, -0.9});
    entity_constructor(&menu->setting[SETTING_RES_PLUS], (entity2_param_t){
    IUTEX_PLUS, (rect_t){{-0.35f, 0.50f},{0.08f, 0.08f}}, -0.9});
    entity_constructor(&menu->setting[SETTING_RES_MINUS], (entity2_param_t){
    IUTEX_MINUS, (rect_t){{-0.58f, 0.50f},{0.08f, 0.08f}}, -0.9});
}

static void menu_set_link_entities(menu_t *menu)
{
    entity_constructor(&menu->link[MENU_LINK_CONTINUE], (entity2_param_t){
    IUTEX_MENU_CONTINUE, (rect_t){{0.75f, -0.30f}, {0.1f, 0.1f}}, -0.999});
    entity_constructor(&menu->link[MENU_LINK_NEW], (entity2_param_t){
    IUTEX_MENU_NEW, (rect_t){{0.75f, -0.40f}, {0.1f, 0.1f}}, -0.999f});
    entity_constructor(&menu->link[MENU_LINK_LOAD], (entity2_param_t){
    IUTEX_MENU_LOAD, (rect_t){{0.75f, -0.50f}, {0.1f, 0.1f}}, -0.999f});
    entity_constructor(&menu->link[MENU_LINK_SETTING], (entity2_param_t){
    IUTEX_MENU_SETTINGS, (rect_t){{0.75f, -0.60f}, {0.1f, 0.1f}}, -0.999f});
    entity_constructor(&menu->link[MENU_LINK_CREDITS], (entity2_param_t){
    IUTEX_MENU_CREDITS, (rect_t){{0.75f, -0.70f}, {0.1f, 0.1f}}, -0.999f});
    entity_constructor(&menu->link[MENU_LINK_QUIT], (entity2_param_t){
    IUTEX_MENU_QUIT, (rect_t){{0.75f, -0.80f}, {0.1f, 0.1f}}, -0.999f});
    entity_constructor(&menu->link[MENU_LINK_CURSOR], (entity2_param_t){
    IUTEX_MENU_CURSOR, (rect_t){{0.65f, -0.40f}, {0.1f, 0.1f}}, -0.999f});
    setting_set_entities(menu);
}

void menu_set_entities(menu_t *menu)
{
    entity_constructor(&menu->background[MENU_BG_MAIN], (entity2_param_t){
    IUTEX_MENU_MAIN, (rect_t){{-1.0f, -1.0f}, {2.0f, 2.0f}}, -0.888f});
    entity_constructor(&menu->background[MENU_BG_SETTING], (entity2_param_t){
    IUTEX_SETTING_BG, (rect_t){{-1.0f, -1.0f}, {2.0f, 2.0f}}, -0.889f});
    menu_set_link_entities(menu);
}
