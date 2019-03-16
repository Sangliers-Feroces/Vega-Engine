/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** ui_lightmap
*/

#ifndef UI_LIGHTMAP_H_
    #define UI_LIGHTMAP_H_

ui_lm_struct_t ui_lm_init(demo_t *demo);

void ui_lm_set_texture_array(ui_lm_struct_t *ui_lm_struct,
const ui_lm_tex_desc_t texture_desc_array[]);


void ui_lightmap_display(demo_t *demo);

void ui_lightmap_draw_background(button_t bg);

#endif /* !UI_LIGHTMAP_H_ */
