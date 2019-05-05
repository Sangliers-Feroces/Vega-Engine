/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** intro
*/

#include "headers.h"

static int check_music_match_time(sfTime expected, musics_t index)
{
    sfTime current_time = sfMusic_getPlayingOffset(
    _demo->sounds.musics[index].sample);

    if (current_time.microseconds >= expected.microseconds)
        return 1;
    return 0;
}

static int intro_poll_event(int *skip_intro)
{
    if (!demo_poll_events(_demo)) {
        (*skip_intro) = 2;
        return 0;   
    }
    if (_demo->input.key_press[KEY_ENTER])
        (*skip_intro) = 0;
    return 1;
}

static void display_val_man(char *vm_step)
{
    glUseProgram(_demo->shader[SHADER_FONT].program);
    glBindVertexArray(_iu.data.vertex_array);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _iu.textures[IUTEX_INTRO_VM]->id);
    iu_display_char((*vm_step), (rect_t){{-0.20f, -0.20f}, {0.5f, 0.7f}},
    FONT_VM);
    /*if (check_music_match_time((sfTime){100000}, MUSICS_VALVE))
        (*vm_step) += 10;
    if (check_music_match_time((sfTime){200000}, MUSICS_VALVE))
        (*vm_step) += 10;
    if (check_music_match_time((sfTime){300000}, MUSICS_VALVE))
        (*vm_step) += 10;*/
}

static void draw_intro(int vm_d, char *vm_step)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (vm_d)
        display_val_man(vm_step);
    glUseProgram(_demo->shader[SHADER_IU].program);
    iu_entity_draw(_iu.intro[BG]);
    sfRenderWindow_display(_demo->win.window);
}

int intro(void)
{
    int skip_intro = 1;
    int display_vm = 1;
    char vm_step = 0;

    play_new_music(MUSICS_VALVE, 0, 100);
    while (!check_music_match_time((sfTime){16000000}, MUSICS_VALVE)
    && intro_poll_event(&skip_intro) && skip_intro) {
        if (check_music_match_time((sfTime){6000000}, MUSICS_VALVE)) {
            _iu.intro[BG].index = IUTEX_INTRO_DEV;
            display_vm = 0;
        }
        if (check_music_match_time((sfTime){10000000}, MUSICS_VALVE))
            _iu.intro[BG].index = IUTEX_INTRO_ENG;
        draw_intro(display_vm, &vm_step);
    }
    if (skip_intro == 2)
        return 0;
    return 1;
}