/*
** EPITECH PROJECT, 2019
** MUL_my_world_2018
** File description:
** menu
*/

#ifndef MENU_H_
    #define MENU_H_

int start(demo_t *demo);

void menu_init(menu_t *menu);

void menu_set_entities(menu_t *menu);

int menu_loop(demo_t *demo, menu_t *menu);

void menu_draw(menu_t *menu);
void setting_draw(menu_t *menu);
void menu_setting_loop(demo_t *demo, menu_t *menu);

int menu_poll_events(demo_t *demo, menu_t *menu);

int analyse_setting_input(demo_t *demo, menu_t *menu);
void setting_buttons_effects(demo_t *demo, menu_t *menu, setting_entity_t choice);

void setting_apply_changes(demo_t *demo,menu_t *menu);

float menu_slider_move(demo_t *demo, menu_t *menu);
#endif /* !MENU_H_ */
