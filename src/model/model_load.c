/*
** EPITECH PROJECT, 2019
** teck1
** File description:
** model_load
*/

#include "headers.h"

mesh_full_t *load_obj(const char *filepath)
{
    mesh_full_t *obj = mesh_full_create(-1, 0);
    char line[128];
    FILE *file = fopen(filepath, "rb");
    int res;
    vec3 pos;
    vec2 uv;
    vec3 normal;
    vertex_t vert;

    while (1) {
        res = fscanf(file, "%s", line);
        if (res == EOF)
            break;
        if (strcmp(line, "v") == 0)
            fscanf(file, "%f %f %f", pos.x, pos.y, pos.z);
        else if (strcmp(line, "vt" ) == 0)
            fscanf(file, "%f %f", uv.x, uv.y );
        else if (strcmp(line, "vn" ) == 0)
            fscanf(file, "%f %f %f", normal.x, normal.y, normal.z);
        vert = vertex_init(pos, normal, uv);
        obj = 
    }
    return (obj);
}