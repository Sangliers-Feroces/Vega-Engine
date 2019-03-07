/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** serialization for the GPU
*/

#include "headers.h"

static int32_t serialize_rec(octree *tree, gpu_serial_t *serial)
{
    int32_t res = serial->size;

    if (tree == NULL)
        return 0;
    serial->size += 8;
    gpu_serial_write_vec3(serial, tree->bounds.min);
    gpu_serial_write_vec3(serial, tree->bounds.max);
    gpu_serial_write(serial,
    vec_rtx_triangle_serialize(&tree->triangles, serial));
    for (size_t i = 0; i < 8; i++)
        serial->data[res + i] = serialize_rec(tree->sub[i], serial);
    return res;
}

gpu_serial_t octree_serialize(octree *tree)
{
    gpu_serial_t res = {octree_serialize_get_size(tree), 1, NULL};

    res.data = malloc_safe(res.buf_size * sizeof(int32_t));
    res.data[0] = 0;
    serialize_rec(tree, &res);
    return res;
}