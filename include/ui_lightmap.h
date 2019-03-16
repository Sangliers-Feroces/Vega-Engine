/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** ui_lightmap
*/

#ifndef UI_LIGHTMAP_H_
    #define UI_LIGHTMAP_H_

void ui_lightmap_set_buttons(void);

void ui_lightmap_display(demo_t *demo);

int ui_lm_poll_events(demo_t *demo);

void ui_lightmap_draw();

void refresh_display_nbr_array(size_t new_value);
#endif /* !UI_LIGHTMAP_H_ */
