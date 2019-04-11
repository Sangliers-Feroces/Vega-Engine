/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#pragma once

typedef struct {
    ssize2 pos;
    octree *tree;
    size_t world_ndx;
} chunk_t;

typedef struct {
    size_t chunk_count;
    size_t chunk_allocated;
    chunk_t **chunk;        // used for rendering
    srect chunk2d_area;
    chunk_t **chunk2d;      // 2d array for fast lookup
} world_t;
