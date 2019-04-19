/*
** EPITECH PROJECT, 2019
** MUL_my_world_2018
** File description:
** iu
*/

#include "headers.h"

static const iutex_path_t iutex_path [] = {
    {IUTEX_ELON, "res/ui/elon.jpg"},
    {IUTEX_PLUS, "res/ui/plus.png"},
    {IUTEX_MINUS, "res/ui/minus.png"},
    {IUTEX_MENU_MAIN, "res/ui/menu/new/menu.png"},
    {IUTEX_MENU_CONTINUE, "res/ui/menu/new/menu_continue.png"},
    {IUTEX_MENU_LOAD, "res/ui/menu/new/menu_load.png"},
    {IUTEX_MENU_LOAD_FADE, "res/ui/menu/new/menu_load_fade.png"},
    {IUTEX_MENU_NEW, "res/ui/menu/new/menu_new.png"},
    {IUTEX_MENU_SETTINGS, "res/ui/menu/new/menu_setting.png"},
    {IUTEX_MENU_CREDITS, "res/ui/menu/new/menu_credits.png"},
    {IUTEX_MENU_QUIT, "res/ui/menu/new/menu_quit.png"},
    {IUTEX_MENU_CURSOR, "res/ui/menu/new/cursor.png"},
    {IUTEX_EDITOR_GRAB, "res/model/editor/grab.png"},
    {IUTEX_EDITOR_SELECT, "res/model/editor/select.png"},
    {IUTEX_SETTING_BG, "res/ui/menu/new/setting_bg.png"},
    {IUTEX_SETTING_RES, "res/ui/menu/new/settings/setting_resolution.png"},
    {IUTEX_SETTING_RES_1920_1080,
    "res/ui/menu/new/settings/setting_res_1920x1080.png"},
    {IUTEX_SETTING_RES_1600_900,
    "res/ui/menu/new/settings/setting_res_1600x900.png"},
    {IUTEX_SETTING_CONFIRM, "res/ui/menu/new/settings/confirmation.png"},
    {IUTEX_SETTING_VOL_BACK, "res/ui/menu/new/settings/volume.png"},
    {IUTEX_SLIDER, "res/ui/menu/new/settings/slider.png"},
    {IUTEX_INVENT_BG, "res/ui/invent/invent.png"},
    {IUTEX_TEXT_CADRE, "res/ui/dialogue_cadre.png"},
    {IUTEX_FONT_MINECRAFT, "res/ui/font/minecraft.png"},
    {0, NULL}
};

static void iu_set_gl(void)
{
    const vec2 vertex_array_base[] =
    {{0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 0.0f},
    {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}};

    _iu.data.iu_program = shader_load_vert_frag("src/gpu/shader/ui_vertex.glsl"
    ,"src/gpu/shader/ui_fragment.glsl");
    if (_iu.data.iu_program == 0) {
        printf("Can't load ui shader.\n");
        exit(84);
    }
    glGenVertexArrays(1, &_iu.data.vertex_array);
    glBindVertexArray(_iu.data.vertex_array);
    glGenBuffers(1, &_iu.data.vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, _iu.data.vertex_buffer);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
    sizeof(vec2), BUFFER_OFFSET(0));
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * 6,
    (glvoid*)vertex_array_base, GL_STATIC_DRAW);
    _iu.data.is_invent = 0;
}

static int iu_check_texture_array(void)
{
    for (int i = 0; i < IUTEX_END; i++) {
        if (_iu.textures[i] == NULL) {
            my_fd_putstr("Can't open textures ", 2);
            putnbr(i, 10, 0);
            my_fd_putchar('\n', 2);
            return 0;
        }
    }
    return 1;
}

static void iu_set_texture(void)
{
    for (int i = 0; i < IUTEX_END; i++)
        _iu.textures[i] = NULL;
    for (int i = 0; iutex_path[i].path != NULL; i++)
        _iu.textures[iutex_path[i].index] =
        texture2_load(iutex_path[i].path);
}

void iu_init(demo_t *demo)
{
    _iu.data.ratiowh = demo->cam.ratiowh;
    iu_set_texture();
    if (!iu_check_texture_array())
        exit(84);
    set_entities();
    iu_text_init();
    iu_set_gl();
    iu_set_font();
}

void iu_quit(void)
{
    for (int i = 0; i < IUTEX_END; i++)
        texture2_destroy(_iu.textures[i]);
    glDeleteVertexArrays(1, &_iu.data.vertex_array);
    glDeleteBuffers(1, &_iu.data.vertex_buffer);
    glDeleteProgram(_iu.data.iu_program);
}
