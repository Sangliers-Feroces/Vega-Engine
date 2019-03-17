/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** menu
*/

#include "headers.h"

static void menu_set_object(menu_t *menu)
{
    menu->object[MENUOBJECT_ELON] =
    (button_t){UIRES_MENU_ELON, (vec2){-1.0f, -1.0f}, 1.0f, -0.999f, REL_X};
    menu->object[MENUOBJECT_INTRO] =
    (button_t){UIRES_MENU_INTRO, (vec2){-1.0f, -1.0f}, 1.0f, -0.999f, REL_X};
    menu->object[MENUOBJECT_DEV] =
    (button_t){UIRES_MENU_DEV, (vec2){-1.0f, -1.0f}, 1.0f, -0.999f, REL_X};
    menu->object[MENUOBJECT_ENGINE] =
    (button_t){UIRES_MENU_ENGINE, (vec2){-1.0f, -1.0f}, 1.0f, -0.999f, REL_X};
    menu->object[MENUOBJECT_MENU] =
    (button_t){UIRES_MENU_MENU, (vec2){0.0f, 0.0f}, 0.0f, -0.888f, REL_X};
    menu->object[MENUOBJECT_PLAY] =
    (button_t){UIRES_MENU_PLAY, (vec2){-0.85f, -0.20f}, 0.50f, -0.999f, REL_X};
    menu->object[MENUOBJECT_QUIT] =
    (button_t){UIRES_MENU_QUIT, (vec2){-0.85f, -0.45f}, 0.20f, -0.9f, REL_X};
    menu->object[MENUOBJECT_CURSOR] =
    (button_t){UIRES_MENU_CURSOR, (vec2){-0.30f, -0.22f}, 0.1f, -0.9f, REL_X};
}

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

int menu(demo_t *demo)
{
    sfMusic *menu_music = sfMusic_createFromFile("res/musics/menu_music.ogg");
    menu_t menu;

    set_sound(&menu);
    menu.intro_state = 0;
    menu.menu_state = 1;
    menu.last_return = 0;
    menu.cur_return = 0;
    menu_set_object(&menu);
    menu_intro(demo, &menu);
    sfMusic_play(menu_music);
    if (!menu_draw(demo, &menu)) {
        music_destroy(&menu, menu_music);
        return 0;
    }
    sfMusic_stop(menu_music);
    music_destroy(&menu, menu_music);
    return 1;
}
