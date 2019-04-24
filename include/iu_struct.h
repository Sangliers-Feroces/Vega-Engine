/*
** EPITECH PROJECT, 2019
** MUL_my_world_2018
** File description:
** iu_struct
*/

#pragma once

typedef enum {
    IUTEX_ELON,
    IUTEX_PLUS,
    IUTEX_MINUS,
    IUTEX_SLIDER,
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
    IUTEX_EDITOR_GRAB,
    IUTEX_EDITOR_SELECT,
    IUTEX_SETTING_RES,
    IUTEX_SETTING_CONFIRM,
    IUTEX_SETTING_RES_1600_900,
    IUTEX_SETTING_RES_1920_1080,
    IUTEX_SETTING_VOL_BACK,
    IUTEX_INVENT_BG,
    IUTEX_TEXT_CADRE,
    IUTEX_FONT_MINECRAFT,
    IUTEX_END
} iutex_t;

typedef enum {
    IUBUTTON_ELON,
    IUBUTTON_CADRE,
    IUBUTTON_END
} iubutton_t;

typedef enum {
    IUINVENT_BG,
    IUINVENT_END
} iuinvent_t;

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

typedef enum {
    DIALOGUE_WELCOME,
    DIALOGUE_END
} dialogues_list_t;

typedef struct {
    iutex_t index;
    int cols;
    int lines;
} font_t;

typedef struct {
    iutex_t index;
    char *path;
} iutex_path_t;

typedef struct {
    iutex_t index;
    rect_t rect;
    float depth;
} entity2_param_t;

struct entity2 {
    iutex_t index;
    rect_t rect;
    float depth;
    rel_t rel;
    pattern_t pattern;
    struct entity2 *slider;
    float x_min;
    float x_max;
};
typedef struct entity2 entity2_t;

typedef struct {
    int ratiowh;
    gluint vertex_array;
    gluint vertex_buffer;
    int is_invent;
    int is_focus;
} iu_data_t;

typedef struct {
    iu_data_t data;
    texture2 *textures[IUTEX_END];
    entity2_t buttons[IUBUTTON_END];
    entity2_t invent[IUINVENT_END];
    entity2_t cadre[IUCADRE_END];
    //texts
    font_t fonts[FONT_END];
    char *text_src[TEXT_END];
    dialogues_list_t current_dialogue;
    vg_dialogue dialogue_list[DIALOGUE_END];
} iu_t;
