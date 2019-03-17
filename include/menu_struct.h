/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** menu_struct
*/

#ifndef MENU_STRUCT_H_
#define MENU_STRUCT_H_

typedef enum {
    MENUOBJECT_ELON,
    MENUOBJECT_INTRO,
    MENUOBJECT_MENU,
    MENUOBJECT_PLAY,
    MENUOBJECT_QUIT,
    MENUOBJECT_CURSOR,
    MENUOBJECT_END,
    MENUOBJECT_NOOBJ
} menuobject_t;

typedef struct {
    int intro_state;
    int menu_state;
    menuobject_t button_clicked;
    button_t object[MENUOBJECT_END];
    int last_return;
    int cur_return;
} menu_t;

#endif /* !MENU_STRUCT_H_ */
