/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static void set_vertex_attrib(gluint vertex_array, gluint vertex_buffer)
{
    glBindVertexArray(vertex_array);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
    sizeof(vertex_t), BUFFER_OFFSET(0));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
    sizeof(vertex_t), BUFFER_OFFSET(offsetof(vertex_t, normal)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
    sizeof(vertex_t), BUFFER_OFFSET(offsetof(vertex_t, uv)));
}

static void set_vertex_ext_attrib(gluint vertex_array,
gluint vertex_buffer, gluint vertex_ext_buffer)
{
    size_t stride = sizeof(vertex_t) + sizeof(vertex_ext_t);

    glBindVertexArray(vertex_array);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
    stride, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
    stride, BUFFER_OFFSET(offsetof(vertex_t, normal)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
    stride, BUFFER_OFFSET(offsetof(vertex_t, uv)));
    glBindBuffer(GL_ARRAY_BUFFER, vertex_ext_buffer);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
    stride, BUFFER_OFFSET(sizeof(vertex_t)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE,
    stride, BUFFER_OFFSET(sizeof(vertex_t) + offsetof(vertex_ext_t, uv_ext)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE,
    stride, BUFFER_OFFSET(sizeof(vertex_t) + offsetof(vertex_ext_t, tex_a)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE,
    stride, BUFFER_OFFSET(sizeof(vertex_t) + offsetof(vertex_ext_t, tex_b)));
}

static void mesh_gpu_init(mesh_t *mesh)
{
    mesh->gpu.do_upload = 1;
    mesh->gpu.do_reupload = 0;
    glGenVertexArrays(1, &mesh->gpu.vertex_array);
    glGenBuffers(1, &mesh->gpu.vertex_buffer);
    set_vertex_attrib(mesh->gpu.vertex_array, mesh->gpu.vertex_buffer);
}

static void mesh_ext_gpu_init(mesh_full_t *mesh)
{
    mesh->gpu.do_upload = 1;
    mesh->gpu.do_reupload = 0;
    glGenVertexArrays(1, &mesh->gpu.vertex_array);
    glGenBuffers(1, &mesh->gpu.vertex_buffer);
    set_vertex_ext_attrib(mesh->gpu.vertex_array, mesh->mesh->gpu.vertex_buffer,
    mesh->gpu.vertex_buffer);
}

static void mesh_gpu_destroy(mesh_gpu_t gpu)
{
    if (gpu.do_upload) {
        glDeleteVertexArrays(1, &gpu.vertex_array);
        glDeleteBuffers(1, &gpu.vertex_buffer);
    }
}

mesh_t* mesh_create(size_t vertex_count, int gpu_do_upload)
{
    mesh_t *res = (mesh_t*)malloc_safe(sizeof(mesh_t));

    res->vertex_count = vertex_count;
    res->vertex_allocated = vertex_count;
    res->vertex =
    (vertex_t*)malloc_safe(res->vertex_allocated * sizeof(vertex_t));
    if (gpu_do_upload)
        mesh_gpu_init(res);
    else
        res->gpu = (mesh_gpu_t){0, 0, 0, 0};
    return res;
}

void mesh_destroy(mesh_t *mesh)
{
    mesh_gpu_destroy(mesh->gpu);
    free(mesh->vertex);
    free(mesh);
}

void mesh_add_vertex(mesh_t *mesh, vertex_t vertex)
{
    size_t cur = mesh->vertex_count++;
    vertex_t *new_vertex;

    if (mesh->vertex_count > mesh->vertex_allocated) {
        mesh->vertex_allocated += 64;
        new_vertex =
        (vertex_t*)malloc_safe(mesh->vertex_allocated * sizeof(vertex_t));
        for (size_t i = 0; i < cur; i++)
            new_vertex[i] = mesh->vertex[i];
        free(mesh->vertex);
        mesh->vertex = new_vertex;
    }
    mesh->vertex[cur] = vertex;
    if (mesh->gpu.do_upload)
        mesh->gpu.do_reupload = 1;
}

void mesh_add_triangle(mesh_t *mesh, vertex_t *triangle)
{
    for (size_t i = 0; i < 3; i++)
        mesh_add_vertex(mesh, triangle[i]);
}

void mesh_add_triangle_pos_uv(mesh_t *mesh, vec3 *pos, vec2 *uv)
{
    vec3 normal = normal3(pos[0], pos[1], pos[2]);

    for (size_t i = 0; i < 3; i++)
        mesh_add_vertex(mesh, vertex_init(pos[i], normal, uv[i]));
}

mesh_full_t* mesh_full_create(size_t vertex_count, int gpu_do_upload,
int has_ext)
{
    mesh_full_t *res = (mesh_full_t*)malloc_safe(sizeof(mesh_full_t));

    res->mesh = mesh_create(vertex_count, gpu_do_upload);
    res->has_ext = has_ext;
    if (has_ext) {
        res->ext_count = vertex_count;
        res->ext_allocated = vertex_count;
        res->ext =
        (vertex_ext_t*)malloc_safe(vertex_count * sizeof(vertex_ext_t));
        mesh_ext_gpu_init(res);
    } else {
        res->ext_count = 0;
        res->ext_allocated = 0;
        res->ext = NULL;
        res->gpu = (mesh_gpu_t){0, 0, 0, 0};
    }
    return res;
}

void mesh_full_destroy(mesh_full_t *mesh)
{
    if (mesh->has_ext)
        mesh_gpu_destroy(mesh->gpu);
    mesh_destroy(mesh->mesh);
    free(mesh->ext);
    free(mesh);
}

void mesh_full_ensure_coherence(mesh_full_t *mesh)
{
    if (mesh->has_ext)
        if (mesh->ext_count != mesh->mesh->vertex_count) {
            printf(
            "Error: incoherent mesh_full: %zu vertex and %zu extensions.\n",
            mesh->mesh->vertex_count, mesh->ext_count);
            exit(84);
        }
}

void mesh_full_add_vertex(mesh_full_t *mesh, vertex_t vertex)
{
    mesh_add_vertex(mesh->mesh, vertex);
    mesh_full_ensure_coherence(mesh);
}

void mesh_full_add_vertex_ext(mesh_full_t *mesh, vertex_t vertex,
vertex_ext_t ext)
{
    size_t cur = mesh->ext_count++;
    vertex_ext_t *new_ext;

    if (mesh->ext_count > mesh->ext_allocated) {
        mesh->ext_allocated += 64;
        new_ext =
        (vertex_ext_t*)malloc_safe(mesh->ext_allocated * sizeof(vertex_ext_t));
        for (size_t i = 0; i < cur; i++)
            new_ext[i] = mesh->ext[i];
        free(mesh->ext);
        mesh->ext = new_ext;
    }
    mesh->ext[cur] = ext;
    if (mesh->gpu.do_upload)
        mesh->gpu.do_reupload = 1;
    mesh_full_add_vertex(mesh, vertex);
    mesh_full_ensure_coherence(mesh);
}