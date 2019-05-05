/*
** EPITECH PROJECT, 2019
** teck1
** File description:
** model_load
*/

#include "headers.h"

static void go_to_token(const char *str, size_t *i, char token)
{
    for (; (str[*i] != token) && (str[*i] != '\0'); (*i)++);
}

size3 model_load_extract_ndx(const char *line, size_t start)
{
    size3 res = {~0ULL, ~0ULL, ~0ULL};
    size_t i = start;

    go_to_token(line, &i, '/');
    if (line[i] == '\0')
        return res;
    if (line[i + 1] == '/')
        sscanf(&line[start], "%zu//%zu", &res.x, &res.z);
    else
        sscanf(&line[start], "%zu/%zu/%zu", &res.x, &res.y, &res.z);
    res.x--;
    res.y--;
    res.z--;
    return res;
}
