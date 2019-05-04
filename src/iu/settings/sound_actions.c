/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** sound_actions
*/

#include "headers.h"

void play_new_music(musics_t index)
{
    if (_demo->sounds.curr_music != NO_MUSIC)
        sfMusic_stop(_demo->sounds.musics[_demo->sounds.curr_music]);
    sfMusic_play(_demo->sounds.musics[index]);
}

void stop_current_music(void)
{
    if (_demo->sounds.curr_music != NO_MUSIC)
        sfMusic_stop(_demo->sounds.musics[_demo->sounds.curr_music]);
}   

void refresh_sound_volume(void)
{
    for (int i = 0; i < MUSICS_END; i++)
        sfMusic_setVolume(_demo->sounds.musics[i],
        (_demo->sounds.music_vol * _demo->sounds.master_vol));
    for (int i = 0; i < SOUNDS_END; i++)
        sfSound_setVolume(_demo->sounds.sounds[i],
        (_demo->sounds.sound_vol * _demo->sounds.master_vol));
}

void play_new_sound(sounds_t index)
{
    sfSound_play(_demo->sounds.sounds[index]);
}