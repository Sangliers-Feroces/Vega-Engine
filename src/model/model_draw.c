/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static void send_mvp(demo_t *demo, entity_t *entity)
{
    mat4 model;
    mat4 mvp;

    mat4_model(entity->pos, entity->scale, entity->rot, model);
    mat4_mul(demo->cam.mvp.vp, model, mvp);
    glUniformMatrix4fv(demo->editor.mvp, 1, GL_FALSE, &mvp[0][0]);
}

void entity_draw(demo_t *demo, entity_t *entity)
{
    glUseProgram(demo->editor.shader);
    glBindBuffer(GL_ARRAY_BUFFER, entity->model->buffer);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
    sizeof(vertex_t), BUFFER_OFFSET(0));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
    sizeof(vertex_t), BUFFER_OFFSET(offsetof(vertex_t, uv)));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, entity->model->texture->id);
    send_mvp(demo, entity);
    glDrawArrays(GL_TRIANGLES, 0, entity->model->vertex_count);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
