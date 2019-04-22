/*
** EPITECH PROJECT, 2019
** MUL_my_world_2018
** File description:
** iu_draw
*/

#include "headers.h"


void iu_draw_full_rel(iutex_t index, rect_t rect, float depth)
{
    gluint pos_id = glGetUniformLocation(_iu.data.iu_program, "pos");
    gluint size_id = glGetUniformLocation(_iu.data.iu_program, "size");
    gluint depth_id = glGetUniformLocation(_iu.data.iu_program, "depth");

    glUniform1f(depth_id, depth);
    glUniform2fv(pos_id, 1, (glfloat *)&rect.p);
    glUniform2fv(size_id, 1, (glfloat *)&rect.s);
    glBindVertexArray(_iu.data.vertex_array);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _iu.textures[index]->id);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void iu_entity_draw(entity2_t entity)
{
    iu_draw_full_rel(entity.index, entity_get_size(entity), entity.depth);
}

static void draw_current_dialogue(void)
{
    if (_iu.current_dialogue == DIALOGUE_END)
        return;
    vg_dialogue_draw(&_iu.dialogue_list[_iu.current_dialogue]);
}

static void temp_dialogue_test(void)
{
    if ((_demo->game_time >= 1.0f && _demo->game_time <= 1.5f)
    && !_iu.dialogue_list[DIALOGUE_WELCOME].read) {
        _iu.dialogue_list[DIALOGUE_WELCOME].read = 1;
        _iu.current_dialogue = DIALOGUE_WELCOME;
    }
}

void iu_display(void)
{
    glUseProgram(_iu.data.iu_program);
    if (_iu.data.is_invent)
        for (int i = 0; i < IUINVENT_END; i++)
            iu_entity_draw(_iu.invent[i]);
    temp_dialogue_test();
    draw_current_dialogue();
}
