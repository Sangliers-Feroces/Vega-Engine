/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

ssize2 file_read_ssize2(file_read_t *file)
{
    ssize2 res;

    file_read(file, &res, sizeof(ssize2));
    return res;
}

arr_dvec3_t file_read_arr_dvec3(file_read_t *file)
{
    arr_dvec3_t res;

    res = arr_dvec3_create(file_read_size_t(file));
    file_read(file, res.dvec3, res.count * sizeof(dvec3));
    return res;
}

chunk_border_t file_read_chunk_border(file_read_t *file)
{
    chunk_border_t res;

    for (size_t i = 0; i < CHUNK_GEN_ITER; i++)
        for (size_t j = 0; j < 2; j++) {
            res.hor[i][j] = file_read_arr_dvec3(file);
            res.ver[i][j] = file_read_arr_dvec3(file);
        }
    return res;
}

static entity3* chunk_seek_tag(entity3 *ent, entity3_tag_t tag)
{
    entity3 *got;

    if (ent->tag == tag)
        return ent;
    for (size_t i = 0; i < ent->sub.count; i++) {
        got = chunk_seek_tag(ent->sub.ent[i], tag);
        if (got != NULL)
            return got;
    }
    return NULL;
}

chunk_t* file_read_chunk(file_read_t *file)
{
    chunk_t *res = chunk_create_detached(file_read_ssize2(file));

    res->border = file_read_chunk_border(file);
    entity3_destroy(res->ents);
    res->ents = file_read_entity3(file, NULL);
    res->terrain = chunk_seek_tag(res->ents, ENTITY3_TAG_TERRAIN);
    return res;
}
