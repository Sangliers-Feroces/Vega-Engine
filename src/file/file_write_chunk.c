/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

void file_write_ssize2(file_write_t *file, ssize2 value)
{
    file_write(file, &value, sizeof(ssize2));
}

void file_write_arr_dvec3(file_write_t *file, arr_dvec3_t arr)
{
    file_write_size_t(file, arr.count);
    file_write(file, arr.dvec3, arr.count * sizeof(dvec3));
}

void file_write_chunk_border(file_write_t *file, chunk_border_t *border)
{
    for (size_t i = 0; i < CHUNK_GEN_ITER; i++)
        for (size_t j = 0; j < 2; j++) {
            file_write_arr_dvec3(file, border->hor[i][j]);
            file_write_arr_dvec3(file, border->ver[i][j]);
        }
}

void file_write_chunk(file_write_t *file, chunk_t *chunk)
{
    file_write_ssize2(file, chunk->pos);
    file_write_chunk_border(file, &chunk->border);
    file_write_entity3(file, chunk->ents);
}
