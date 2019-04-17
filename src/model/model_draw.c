/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

void entity_refresh(entity_t * entity)
{
    for (size_t i = 0; i < entity->model->vertex_count; i++) {
        /*entity->vertex[i].pos = mat4_mul_dvec3(entity->trans,
        entity->model->vertex[i].pos);
        entity->vertex[i].normal = mat4_mul_dvec3(entity->rot_mat,
        entity->model->vertex[i].normal);*/
    }
}

static void send_mvp(demo_t *demo, entity_t *entity)
{
    mat4 mvp;

    mat4_rot(entity->rot, entity->rot_mat);
    mat4_scale_trans(entity->pos, entity->scale, mvp);
    mat4_mul(mvp, entity->rot_mat, entity->trans);
    mat4_mul(demo->cam.mvp.vp, entity->trans, mvp);
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
