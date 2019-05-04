/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** iu_setting_struct
*/

#pragma once

typedef enum {
    SETTINGS_BG,
    SETTINGS_END
} settings_entitie_t;

typedef struct {
    entity2_t entities[SETTINGS_BG];
} settings_t;