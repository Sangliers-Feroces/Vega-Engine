/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** menu
*/

#ifndef MENU_H_
    #define MENU_H_
int menu(demo_t *demo);

int menu_draw(demo_t *demo, menu_t *menu);

int menu_intro(demo_t *demo, menu_t *menu);

int menu_poll_events(demo_t *demo, menu_t *menu);

#endif /* !MENU_H_ */
