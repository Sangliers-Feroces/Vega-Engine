/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** ui_struct
*/

#ifndef UI_STRUCT_H_
#define UI_STRUCT_H_

typedef struct {
    float width;
    float lenght;
} quad_size_t;

typedef enum {
    UIRES_ELON,
    UIRES_CROSS,
    UIRES_PAINT,
    UIRES_TEXTURE,
    UIRES_LIGHTMAPS,
    UIRES_PLAY,
    UIRES_ISO,
    UIRES_CAM,
    UIRES_CADRE,
    UIRES_POURCENT,
    UIRES_RED,
    UIRES_LM_TITLE,
    UIRES_LM_LEGEND,
    UIRES_LM_PLUS,
    UIRES_LM_MINUS,
    UIRES_LM_START,
    UIRES_LM_BACK,
    UIRES_LM_ABORT,
    UIRES_DIGIT_0,
    UIRES_DIGIT_1,
    UIRES_DIGIT_2,
    UIRES_DIGIT_3,
    UIRES_DIGIT_4,
    UIRES_DIGIT_5,
    UIRES_DIGIT_6,
    UIRES_DIGIT_7,
    UIRES_DIGIT_8,
    UIRES_DIGIT_9,
    UIRES_MENU_ELON,
    UIRES_MENU_INTRO,
    UIRES_MENU_DEV,
    UIRES_MENU_ENGINE,
    UIRES_MENU_MENU,
    UIRES_MENU_PLAY,
    UIRES_MENU_QUIT,
    UIRES_MENU_CURSOR,
    UIRES_EDITOR_SELECT,
    UIRES_EDITOR_GRAB,
    UIRES_MAX
} uires_t;

typedef enum {
    UIBUTTON_MOVE,
    UIBUTTON_PAINT,
    UIBUTTON_TEXTURE,
    UIBUTTON_LIGHTMAPS,
    UIBUTTON_PLAY,
    UIBUTTON_ISO,
    UIBUTTON_CAM,
    UIBUTTON_CADRE,
    UIBUTTON_MAX,
    UIBUTTON_NONE
} uibutton_t;

typedef enum {
    UILMBUTTON_TITLE,
    UILMBUTTON_PLUS,
    UILMBUTTON_MINUS,
    UILMBUTTON_LEGEND,
    UILMBUTTON_START,
    UILMBUTTON_BACK,
    UILMBUTTON_ABORT,
    UILMBUTTON_LOADING,
    UILMBUTTON_CADRE,
    UILMBUTTON_POURCENT,
    UILMBUTTON_END,
    UILMBUTTON_NONE
} uilmbutton_t;

typedef struct {
    int index;
    char *path;
}  ui_texture_descriptor_t;

typedef enum {
    REL_X,
    REL_Y
} rel_type_t;

typedef struct {
    uires_t texture_index;
    vec2 pos;
    float size;
    float depth;
    rel_type_t rel;
} button_t;

typedef struct {
    int back;
    uilmbutton_t button_clicked;
    button_t object[UILMBUTTON_END];
} ui_lm_struct_t;

typedef struct {
    int value;
    button_t digit;
} digit_array_t;

typedef struct {
    int nb_digit;
    digit_array_t *digits;
} display_nbr_array_t;

typedef struct {
    int display_ui;
    int selected_texture;
    uibutton_t button_hovered;
    uibutton_t button_clicked;
    gluint ui_program;
    gluint vertex_buffer;
    texture2 *textures[UIRES_MAX];
    button_t buttons[UIBUTTON_MAX];
    float ratiowh;
    ui_lm_struct_t ui_lightmap_struct;
    display_nbr_array_t display_nbr_array;
    display_nbr_array_t loading_pourcent;
    size_t ray_density;
} ui_struct;

#endif /* !UI_STRUCT_H_ */
