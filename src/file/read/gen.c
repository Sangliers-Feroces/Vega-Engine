/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

int file_read_int(file_read_t *file)
{
    int res;

    file_read(file, &res, sizeof(int));
    return res;
}

char* file_read_string(file_read_t *file)
{
    size_t size;
    char *res;

    file_read_actual(file, &size, sizeof(size_t));
    file->i -= sizeof(size_t);
    res = (char*)malloc_safe(size);
    file_read(file, res, size);
    if ((size == 0) || (res[size - 1] != '\0')) {
        printf("Corrupted string.\n");
        exit(84);
    }
    return res;
}
