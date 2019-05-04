/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** sound
*/

#pragma once

void sounds_init(void);

void play_new_music(musics_t index);
void play_new_sound(sounds_t index);
void stop_current_music(void);

void refresh_sound_volume(void);

void sounds_quit(void);