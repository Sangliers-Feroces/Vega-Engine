/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** demo_display
*/

#include "headers.h"

static void send_uniform(demo_t *demo, gluint program)
{
    glint aperture = glGetUniformLocation(program, "aperture");

    glUniform1f(aperture, demo->cam.aperture);
    refresh_vp(demo, demo->buf.lightmap_shader);
}

static void set_vertex_attrib(demo_t *demo)
{
    refresh_vertex_buffer(demo);
    glBindBuffer(GL_ARRAY_BUFFER, demo->buf.vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER,
    sizeof(vertext_array_t) * (demo->buf.vertex_struct.count * 3),
    demo->buf.vertex_struct.v_array, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
    sizeof(vertext_array_t), BUFFER_OFFSET(0));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
    sizeof(vertext_array_t), BUFFER_OFFSET(offsetof(vertext_array_t, uv)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
    sizeof(vertext_array_t), BUFFER_OFFSET(offsetof(vertext_array_t,
    uv_albedo)));
}

static void draw_geom(octree *tree, size_t *i)
{
    if (tree == NULL)
        return;
    if (tree->triangles.count > 0) {
        for (size_t j = 0; j < tree->triangles.count; j++) {
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D,
            tree->triangles.triangle[j]->albelo.texture->id);
            glDrawArrays(GL_TRIANGLES, 0 + (*i * 3), 3);
            (*i)++;
        }
    }
    for (int j = 0; j < 8; j++)
        draw_geom(tree->sub[j], i);
}

static void reset_gl_pipeline(void)
{
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glFrontFace(GL_CW);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void demo_render_geom(demo_t *demo)
{
    size_t index = 0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(demo->buf.lightmap_shader);
    send_uniform(demo, demo->buf.lightmap_shader);
    set_vertex_attrib(demo);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _lightmaps.base->id);
    glFrontFace(GL_CW);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    draw_geom(demo->tree, &index);
    reset_gl_pipeline();
}
