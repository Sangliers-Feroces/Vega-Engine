/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** menu_draw
*/

#include "headers.h"

static void draw_option_menu(menu_t *menu)
{
    rect_t rect = {{-1.0f, -1.0f}, {2.0f, 2.0f}};

    ui_draw_full_rel(menu->object[MENUOBJECT_MENU].texture_index,
    rect, menu->object[MENUOBJECT_MENU].depth);
    for (size_t i  = MENUOBJECT_PLAY; i <= MENUOBJECT_CURSOR; i++)
        button_draw(menu->object[i]);
}


void draw_intro(demo_t *demo, button_t object)
{
    rect_t rect = {{-1.0f, -1.0f}, {2.0f, 2.0f}};

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(_ui.ui_program);
    glFrontFace(GL_CW);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    ui_draw_full_rel(object.texture_index, rect, object.depth);
    sfRenderWindow_display(demo->win.window);
}

int menu_draw(demo_t *demo, menu_t *menu)
{
    while (menu_poll_events(demo, menu)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(_ui.ui_program);
        glFrontFace(GL_CW);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        draw_option_menu(menu);
        sfRenderWindow_display(demo->win.window);
    }
    return menu->menu_state;
}


