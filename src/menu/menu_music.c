/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** menu_music
*/

#include "headers.h"

int check_music_match_time(sfTime expected, sfMusic *music)
{
    sfTime current_time = sfMusic_getPlayingOffset(music);
    if (current_time.microseconds >= expected.microseconds)
        return 1;
    return 0;
}

void music_destroy(menu_t *menu, sfMusic *music)
{
    sfMusic_destroy(music);
    sfSound_destroy(menu->move);
    sfSound_destroy(menu->select);
}

void set_sound(menu_t *menu)
{
    sfSoundBuffer *select = sfSoundBuffer_createFromFile("res/musics/move.ogg");
    sfSoundBuffer *move = sfSoundBuffer_createFromFile("res/musics/move.ogg");
    
    menu->move = sfSound_create();
    menu->select = sfSound_create();
    sfSound_setBuffer(menu->move, move);
    sfSound_setBuffer(menu->select, select);
    sfSoundBuffer_destroy(move);
    sfSoundBuffer_destroy(select);
}