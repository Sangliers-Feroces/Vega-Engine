/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** init
*/

#include "headers.h"

static const char *fmt = "fullscreen: %d\ndisplay hints: %d\n";

static void load_settings(settings_t *res)
{
    FILE *file = fopen("config.conf", "r");

    if (file == NULL)
        return;
    fscanf(file, fmt, &res->screen_state, &res->hints_state);
    fclose(file);
}

static void store_settings(settings_t to_store)
{
    FILE *file = fopen("config.conf", "w+");

    if (file == NULL)
        return;
    fprintf(file, fmt, to_store.screen_state, to_store.hints_state);
    fclose(file);
}

settings_t settings_load(void)
{
    settings_t res;

    res.hints_state = WITH_HINT;
    res.screen_state = FULLSCREEN;
    load_settings(&res);
    return res;
}

void settings_init(void)
{
    _iu.settings = settings_load();
    setting_set_entities();
}

void settings_quit(void)
{
    store_settings(_iu.settings);
}
