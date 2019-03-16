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
    UINOBUTTON
} uibutton_t;

typedef struct {
    uires_t index;
    char *path;
}  ui_texture_descriptor_t;

typedef enum {
    BUTTON_REL_X,
    BUTTON_REL_Y
} button_rel_type_t;

typedef struct {
    uires_t texture_index;
    vec2 pos;
    float size;
    float depth;
    button_rel_type_t rel;
} button_t;

typedef struct {
    texture2 *textures[UILIGHTMAP_END];
    button_t object;
} ui_lm_struct_t;

typedef struct {
    int selected_texture;
    uibutton_t button_clicked;
    gluint ui_program;
    gluint vertex_buffer;
    texture2 *textures[UIRES_MAX];
    button_t buttons[UIBUTTON_MAX];
    float ratiowh;
    ui_lm_struct_t ui_lightmap_struct;
} ui_struct;

#endif /* !UI_STRUCT_H_ */
