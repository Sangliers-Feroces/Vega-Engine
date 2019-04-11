/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#pragma once

#define CHUNK_SIZE 64.0f

void world_insert_vec_rtx_triangle(demo_t *demo, vec_rtx_triangle vec);

void world_init(demo_t *demo);
void world_quit(demo_t *demo);

chunk_t** world_chunk2d_get(demo_t *demo, ssize2 pos);
void world_chunk2d_insert(demo_t *demo, chunk_t *chunk);
chunk_t* world_chunk_get(demo_t *demo, ssize2 pos);
chunk_t* world_chunk_get_by_pos(demo_t *demo, vec3 pos);

chunk_t* chunk_create(ssize2 pos);
void chunk_destroy(chunk_t *chunk);
void chunk_insert_rtx_triangle(chunk_t *chunk, rtx_triangle *triangle);
