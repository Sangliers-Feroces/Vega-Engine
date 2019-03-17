/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** menu
*/

#include "headers.h"

int menu_intro(demo_t *demo, menu_t *menu)
{
    sfMusic *music = sfMusic_createFromFile("res/musics/music_intro.ogg");
    menuobject_t index = MENUOBJECT_INTRO;

    menu->skip_intro = 0;
    sfMusic_play(music);
    while (!check_music_match_time((sfTime){16000000}, music)
    && menu_poll_events(demo, menu) && !menu->skip_intro) {
        if (check_music_match_time((sfTime){6000000}, music))
            index = MENUOBJECT_DEV;
        if (check_music_match_time((sfTime){10000000}, music))
            index = MENUOBJECT_ENGINE;
        draw_intro(demo, menu->object[index]);
    }
    sfMusic_destroy(music);
    return menu->intro_state;
}

static int set_action(int menu_state)
{
    switch (menu_state) {
        case 0:
            return 1;
        case 1:
            return 0;
    }
    return 0;
}

int menu(demo_t *demo)
{
    sfMusic *menu_music = sfMusic_createFromFile("res/musics/menu_music.ogg");
    menu_t menu;

    set_sound(&menu);
    menu.intro_state = 0;
    menu.menu_state = 0;
    menu.last_return = 0;
    menu.cur_return = 0;
    menu_set_object(&menu);
    menu_intro(demo, &menu);
    sfMusic_play(menu_music);
    if (!set_action(menu_draw(demo, &menu))) {
        music_destroy(&menu, menu_music);
        return 0;
    }
    sfMusic_stop(menu_music);
    music_destroy(&menu, menu_music);
    return 1;
}
