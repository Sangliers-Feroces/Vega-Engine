/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** sound_struct
*/

#pragma once

typedef enum {
    MUSICS_METRO,
    MUSICS_HL2,
    MUSICS_END,
    NO_MUSIC
} musics_t;

typedef enum {
    SOUNDS_SELECT,
    SOUNDS_MOVE_MENU,
    SOUNDS_END
} sounds_t;

typedef struct {
    sounds_t index;
    char *path;
}  sounds_decs_t;

typedef struct {
    musics_t index;
    char *path;
}  musics_decs_t;

typedef struct {
    musics_t curr_music;
    float master_vol;
    float music_vol;
    float sound_vol;
    sfMusic *musics[MUSICS_END];
    sfSoundBuffer *sb[SOUNDS_END];
    sfSound *sounds[SOUNDS_END];
} sound_t;