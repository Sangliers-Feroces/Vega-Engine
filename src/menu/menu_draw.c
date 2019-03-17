/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** menu_draw
*/

#include "headers.h"

void menu_draw_full_rel(menu_t *menu, int index, rect_t rect, float depth)
{
    gluint pos_id = glGetUniformLocation(_ui.ui_program, "pos");
    gluint size_id = glGetUniformLocation(_ui.ui_program, "size");
    gluint depth_id = glGetUniformLocation(_ui.ui_program, "depth");

    glUniform1f(depth_id, depth);
    glUniform2fv(pos_id, 1, (glfloat *)&rect.p);
    glUniform2fv(size_id, 1, (glfloat *)&rect.s);
    glBindBuffer(GL_ARRAY_BUFFER, _ui.vertex_buffer);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
    sizeof(vec2), BUFFER_OFFSET(0));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, menu->textures[index]->id);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(0);
}

static void draw_option_menu(menu_t *menu)
{
    rect_t rect = {{-1.0f, -1.0f}, {2.0f, 2.0f}};
    rect_t rect_play = {{-0.85f, -0.20f}, {0.40f, 0.2f}};
    rect_t rect_quit = {{-0.85f, -0.45f}, {0.25f, 0.15f}};

    menu_draw_full_rel(menu, menu->object[MENUOBJECT_MENU].texture_index,
    rect, menu->object[MENUOBJECT_MENU].depth);
    menu_draw_full_rel(menu, menu->object[MENUOBJECT_QUIT].texture_index,
    rect_quit, menu->object[MENUOBJECT_QUIT].depth);
    menu_draw_full_rel(menu, menu->object[MENUOBJECT_PLAY].texture_index,
    rect_play, menu->object[MENUOBJECT_PLAY].depth);
    menu_draw_full_rel(menu, menu->object[MENUOBJECT_CURSOR].texture_index,
    button_get_size(menu->object[MENUOBJECT_CURSOR]),
    menu->object[MENUOBJECT_CURSOR].depth);
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

int menu_intro(demo_t *demo, menu_t *menu)
{
    rect_t rect = {{-0.50f, -0.50f}, {1.0f, 1.0f}};

    while (menu_poll_events(demo, menu) && !menu->intro_state) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(_ui.ui_program);
        glFrontFace(GL_CW);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        menu_draw_full_rel(menu, menu->object[MENUOBJECT_INTRO].texture_index, rect,
        menu->object[MENUOBJECT_INTRO].depth);
        sfRenderWindow_display(demo->win.window);
    }
    return menu->intro_state;
}