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

void display_dialogues(void)
{
    printf("time elpased : %f\n", _demo->game_time);
    if (_demo->game_time >= 1.0f && _demo->game_time <= 3.0f)
        iu_display_grp(TEXT_GRP_IND_WELCOME);
}

void iu_display(void)
{
    glUseProgram(_iu.data.iu_program);
    if (_iu.data.is_invent)
        for (int i = 0; i < IUINVENT_END; i++)
            iu_entity_draw(_iu.invent[i]);
    //commenter de ici
    for (int i = 0; i < IUBUTTON_END; i++)
        iu_entity_draw(_iu.buttons[i]);
    display_str_temp("Pourquoi la premiere lettre est degueu .?!", (rect_t){{-0.45f, -0.80f}, {0.03f, 0.04f}}, FONT_MINECRAFT);
    // a ici
}
