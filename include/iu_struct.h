/*
** EPITECH PROJECT, 2019
** MUL_my_world_2018
** File description:
** iu_struct
*/

#ifndef IU_STRUCT_H_
    #define IU_STRUCT_H_

typedef enum {
    IUTEX_ELON,
    IUTEX_MENU_MAIN,
    IUTEX_MENU_CONTINUE,
    IUTEX_MENU_LOAD,
    IUTEX_MENU_LOAD_FADE,
    IUTEX_MENU_NEW,
    IUTEX_MENU_SETTINGS,
    IUTEX_MENU_CREDITS,
    IUTEX_MENU_QUIT,
    IUTEX_MENU_CURSOR,
    IUTEX_SETTING_BG,
    IUTEX_TERRAIN,
    IUTEX_EDITOR_GRAB,
    IUTEX_EDITOR_SELECT,
    IUTEX_END
} iutex_t;

typedef enum {
    IUBUTTON_ELON,
    IUBUTTON_END
} iubutton_t;

typedef enum {
    IUREL_X,
    IUREL_Y,
    IUREL_FULL
} rel_t;

typedef enum {
    PATTERN_CLICK_BUTTON,
    PATTERN_SLIDE_BUTTON,
    PATTERN_DRAG_AND_DROP,
    PATTERN_CLASSIC,
    PATTERN_END
} pattern_t;

typedef struct {
    iutex_t index;
    char *path;
} iutex_path_t;

typedef struct {
    iutex_t index;
    rect_t rect;
    float depth;
} entity2_param_t;

typedef struct {
    iutex_t index;
    rect_t rect;
    float depth;
    rel_t rel;
    pattern_t pattern;
} entity2_t;

typedef struct {
    int ratiowh;
    gluint iu_program;
    gluint vertex_buffer;
} iu_data_t;

typedef struct {
    iu_data_t data;
    texture2 *textures[IUTEX_END];
    entity2_t buttons[IUBUTTON_END];
} iu_t;

#endif /* !IU_STRUCT_H_ */
