/*
** EPITECH PROJECT, 2019
** MUL_my_world_2018
** File description:
** menu_struct
*/

#pragma once

#include "menu_setting_struct.h"

typedef enum {
    MENU_BG_MAIN,
    MENU_BG_SETTING,
    MENU_BG_END
} menu_bg_t;

typedef enum {
    MENU_LINK_CONTINUE,
    MENU_LINK_NEW,
    MENU_LINK_LOAD,
    MENU_LINK_SETTING,
    MENU_LINK_CREDITS,
    MENU_LINK_QUIT,
    MENU_LINK_CURSOR,
    MENU_LINK_END
} menu_link_t;

typedef enum {
    SETTING_RES,
    SETTING_RES_CHOICE,
    SETTING_RES_PLUS,
    SETTING_RES_MINUS,
    SETTING_VOL_MASTER,
    SETTING_END
} setting_entity_t;

typedef enum {
    LIST_RES_1600_900,
    LIST_RES_1920_1080,
} resolution_list_t;

typedef struct {
    size_t w;
    size_t h;
    iutex_t index;
} resolutions_t;

typedef enum {
    MENU_BRANCH_ROOT,
    MENU_BRANCH_SETTING,
    MENU_BRANCH_END
} menu_branch_t;

typedef struct {
    int win_h;
    int win_w;
} settings_t;

typedef struct {
    //setting
    int edited_setting;
    settings_t setting_temp;
    //temporaire
    resolution_list_t choosen_res;
    //save
    int first_save;
    //menu_state
    int state;
    int menu_choice;
    menu_branch_t branch;
    //entities
    entity2_t background[MENU_BG_END];
    entity2_t link[MENU_LINK_END];
    entity2_t setting[SETTING_END];
    entity2_t confirmation;
    //music
    sfMusic *music;
} menu_t;
