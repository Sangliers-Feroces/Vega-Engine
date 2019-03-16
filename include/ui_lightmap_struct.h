/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** ui_lightmap_struct
*/

#ifndef UI_LIGHTMAP_STRUCT_H_
    #define UI_LIGHTMAP_STRUCT_H_

typedef enum {
    UILIGHTMAP_BG,
    UILIGHTMAP_END
} uilightmap_t;

/*typedef enum {

} uilmbutton_t*/

typedef struct {
    uilightmap_t index;
    char *path;
} ui_lm_tex_desc_t;
#endif /* !UI_LIGHTMAP_STRUCT_H_ */
