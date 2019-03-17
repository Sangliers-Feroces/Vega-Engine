/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** menu
*/

#ifndef MENU_H_
    #define MENU_H_

int menu(demo_t *demo);

void set_sound(menu_t *menu);

int menu_draw(demo_t *demo, menu_t *menu);
void draw_intro(demo_t *demo, button_t object);
int menu_intro(demo_t *demo, menu_t *menu);

int menu_poll_events(demo_t *demo, menu_t *menu);

void menu_set_object(menu_t *menu);
void display_setting(demo_t *demo, menu_t *menu);

int check_music_end(sfTime music_duration, sfMusic *music);
int check_music_match_time(sfTime expected, sfMusic *music);
void music_destroy(menu_t *menu, sfMusic *music);

#endif /* !MENU_H_ */
