/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** vulkan ftw
*/

#include "headers.h"

static char* get_program_err(gluint program, int is_program)
{
    glint res = GL_FALSE;
    int log_len;
    char *msg = NULL;

    if (is_program) {
        glGetProgramiv(program, GL_COMPILE_STATUS, &res);
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_len);
        if (log_len > 0) {
            msg = malloc_safe(log_len + 1);
            glGetProgramInfoLog(program, log_len, NULL, msg);
        }
    } else {
        glGetShaderiv(program, GL_COMPILE_STATUS, &res);
        glGetShaderiv(program, GL_INFO_LOG_LENGTH, &log_len);
        if (log_len > 0) {
            msg = malloc_safe(log_len + 1);
            glGetShaderInfoLog(program, log_len, NULL, msg);
        }
    }
    return msg;
}

static int check_shader(gluint program, int is_program)
{
    char *msg = get_program_err(program, is_program);

    if (msg == NULL)
        return 1;
    printf("%s\n", msg);
    return 0;
}

gluint shader_load_compute(const char *path)
{
    gluint compute_shader = glCreateShader(GL_COMPUTE_SHADER);
    gluint program;
    char *src = get_file_data(path);

    if (src == NULL)
        printf("Can't open '%s'.\n", path);
    glShaderSource(compute_shader, 1, (const char **)&src , NULL);
    glCompileShader(compute_shader);
    if (!check_shader(compute_shader, 0))
        return 0;
    program = glCreateProgram();
    glAttachShader(program, compute_shader);
    glLinkProgram(compute_shader);
    if (!check_shader(program, 1))
        return 0;
    glDetachShader(program, compute_shader);
    glDeleteShader(compute_shader);
    free(src);
    return program;
}
