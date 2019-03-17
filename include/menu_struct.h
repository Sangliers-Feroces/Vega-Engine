/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** menu_struct
*/

#ifndef MENU_STRUCT_H_
    #define MENU_STRUCT_H_

typedef enum {
    MENURES_ELON,
    MENURES_INTRO,
    MENURES_MENU,
    MENURES_PLAY,
    MENURES_QUIT,
    MENURES_CURSOR,
    MENURES_MAX
} menures_t;

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
    texture2 *textures[MENURES_MAX];
    menuobject_t button_clicked;
    button_t object[MENUOBJECT_END];
} menu_t;

#endif /* !MENU_STRUCT_H_ */
