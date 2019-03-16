/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** ui
*/

#include "headers.h"

static const ui_texture_descriptor_t texture_desc_array[] = {
    {UIRES_ELON, "res/ui/elon.jpg"},
    {UIRES_CROSS, "res/ui/ui_move_button.png"},
    {UIRES_PAINT, "res/ui/ui_paint_button.png"},
    {UIRES_TEXTURE, "res/ui/ui_texture_button.png"},
    {UIRES_LIGHTMAPS, "res/ui/ui_lightmap_button.png"},
    {UIRES_PLAY, "res/ui/ui_play_button.png"},
    {UIRES_ISO, "res/ui/ui_iso_button.png"},
    {UIRES_CAM, "res/ui/ui_reset_button.png"},
    {UIRES_CADRE, "res/ui/ui_cadre_button.png"},
    {UIRES_LM_TITLE, "res/ui/ui_lightmap_tiltle.png"},
    {UIRES_LM_PLUS, "res/ui/ui_lightmap_plus_button.png"},
    {UIRES_LM_MINUS, "res/ui/ui_lightmap_minus_button.png"},
    {UIRES_LM_LEGEND, "res/ui/ui_lightmap_legend.png"},
    {UIRES_LM_START, "res/ui/ui_lightmap_start_button.png"},
    {0, NULL}
};

static int ui_check_texture_array(void)
{
    for (int i = 0; i < UIRES_MAX; i++) {
        if (_ui.textures[i] == NULL) {
            my_fd_putstr("Can't open textures ", 2);
            putnbr(i, 10, 0);
            my_fd_putchar('\n', 2);
            return 0;
        }
    }
    return 1;
}

static void load_gl_stuff(void)
{
    const vec2 vertex_array_base[] =
    {{0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 0.0f},
    {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}};

    _ui.ui_program = shader_load_vert_frag("src/gpu/shader/ui_vertex.glsl",
    "src/gpu/shader/ui_fragment.glsl");
    if (_ui.ui_program == 0) {
        printf("Can't load ui shader.\n");
        exit(84);
    }
    glGenBuffers(1, &_ui.vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, _ui.vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * 6,
    (glvoid*)vertex_array_base, GL_STATIC_DRAW);
}

void ui_init(demo_t *demo)
{
    _ui.ratiowh = demo->cam.ratiowh;
    ui_set_textures_to_null();
    ui_load_texture(texture_desc_array);
    if (!ui_check_texture_array())
        exit(84);
    ui_set_buttons();
    ui_lightmap_set_buttons();
    _ui.selected_texture = 0;
    demo->action = ACTION_MOVE;
    load_gl_stuff();
}

void ui_quit(void)
{
    for (int i = 0; i < UIRES_MAX; i++)
        texture2_destroy(_ui.textures[i]);
    glDeleteBuffers(1, &_ui.vertex_buffer);
    glDeleteProgram(_ui.ui_program);
}
