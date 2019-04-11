/*
** EPITECH PROJECT, 2019
** MUL_my_world_2018
** File description:
** menu_struct
*/

#ifndef MENU_STRUCT_H_
    #define MENU_STRUCT_H_

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
    MENU_BRANCH_ROOT,
    MENU_BRANCH_SETTING,
    MENU_BRANCH_END
} menu_branch_t;

typedef struct {
    int first_save;
    int state;
    int menu_choice;
    menu_branch_t branch;
    entity2_t background[MENU_BG_END];
    entity2_t link[MENU_LINK_END];
} menu_t;
#endif /* !MENU_STRUCT_H_ */
