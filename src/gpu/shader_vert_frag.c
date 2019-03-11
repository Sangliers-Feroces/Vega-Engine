/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** shader_vert_frag
*/

#include "headers.h"

static int compile_shaders(gluint *vertex_shader_id, gluint *fragment_shader_id,
const char *vertex_filepath, const char *fragment_filepath)
{
    char *vertex_shader_pointer = get_file_data(vertex_filepath);
    char *fragment_shader_pointer = get_file_data(fragment_filepath);
    int returned = 1;

    glShaderSource(*vertex_shader_id, 1, 
    (const char **)&vertex_shader_pointer, NULL);
    glCompileShader(*vertex_shader_id);
    if (!shader_check(*vertex_shader_id, 0))
        returned = 0;
    glShaderSource(*fragment_shader_id, 1,
    (const char **)&fragment_shader_pointer, NULL);
    glCompileShader(*fragment_shader_id);
    if (!shader_check(*fragment_shader_id, 0))
        returned = 0;
    free(vertex_shader_pointer);
    free(fragment_shader_pointer);
    return returned;
}

gluint shader_load_vert_frag(const char *vertex_filepath,
const char *fragment_filepath)
{
    gluint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    gluint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    gluint program;

    if (!compile_shaders(&vertex_shader_id, &fragment_shader_id,
    vertex_filepath, fragment_filepath))
        return 0;
    program = glCreateProgram();
    glAttachShader(program, vertex_shader_id);
    glAttachShader(program, fragment_shader_id);
    glLinkProgram(program);
    if (!shader_check(program, 1))
        return 0;
    glDetachShader(program, vertex_shader_id);
    glDeleteShader(vertex_shader_id);
    glDetachShader(program, fragment_shader_id);
    glDeleteShader(fragment_shader_id);
    return program;
}
