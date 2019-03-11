/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** shader_vert_frag
*/

#include "headers.h"

int compile_shaders(gluint *vertex_array_id, gluint *fragment_shader_id,
const char *vertex_filepath, const char *fragment_filepath)
{
    char *vertex_shader_pointer = get_file_data(vertex_filepath);
    char *fragment_shader_pointer = get_file_data(fragment_filepath);
    int returned = 1;

    glShaderSource(*vertex_array_id, 1, 
    (const char **)&vertex_shader_pointer, NULL);
    glCompileShader(*vertex_array_id);
    if (!shader_check(*vertex_array_id, 0))
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

gluint load_shader(const char *vertex_filepath, const char *fragment_filepath)
{
    gluint vertex_array_id = glCreateShader(GL_VERTEX_SHADER);
    gluint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    gluint program;

    if (!compile_shaders(&vertex_array_id, &fragment_shader_id,
    vertex_filepath, fragment_filepath))
        return 0;
    program = glCreateProgram();
    glAttachShader(program, vertex_array_id);
    glAttachShader(program, fragment_shader_id);
    glLinkProgram(program);
    if (!shader_check(program, 1))
        return 0;
    glDetachShader(program, vertex_array_id);
    glDeleteShader(vertex_array_id);
    glDetachShader(program, fragment_shader_id);
    glDeleteShader(fragment_shader_id);
    return program;
}