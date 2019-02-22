/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** hidden stuff. don't look !
*/

#include "headers.h"

/* full shenanigans */

void exit_full_custom(void)
{
    __asm__("mov $60, %rax");
    __asm__("mov $84, %rdi");
    __asm__("syscall");
}

void* malloc_safe(size_t size)
{
    void *res;

    res = malloc(size);
    if (res == NULL)
        exit_full_custom();
    return (res);
}

float randf(void)
{
    return ((float)rand() / (float)RAND_MAX);
}

uint32_t swap32(uint32_t base)
{
    return ((base >> 24) & 0xFF) | ((base >> 16) & 0xFF00) |
    ((base >> 8) & 0xFF0000) | ((base >> 0) & 0xFF000000);
}

char* get_file_data(const char *path)
{
    FILE *file;
    char *data;
    size_t size = 65536;
    size_t got;

    file = fopen(path, "rb");
    if (file == NULL)
        return NULL;
    do {
        data = (char*)malloc_safe((size + 1) * sizeof(char));
        got = fread(data, 1, size, file);
        if (got < size)
            break;
        free(data);
        size *= 2;
        rewind(file);
    } while (1);
    fclose(file);
    data[got] = '\0';
    return data;
}
