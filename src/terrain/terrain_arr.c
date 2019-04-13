/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static vec3 mid_triangle(vec3 a, vec3 b, vec3 c)
{
    float dist = vec3_dist(b, c);
    vec3 normal = normal3(a, b, c);
    vec3 mid = vec3_add(
    vec3_divs(vec3_add(b, c), 2.0f),
    vec3_muls(normal, (randf() - 0.5f) * dist * 0.30f));

    return mid;
}

static void split_ter(arr2d_vec3_t *arr)
{
    arr2d_vec3_t new_arr = arr2d_vec3_create(arr->w * 2 - 1, arr->h * 2 - 1);

    for (size_t i = 0; i < arr->h; i++)
        for (size_t j = 0; j < arr->w; j++)
            new_arr.vec3[i * 2 * new_arr.w + j * 2] = arr->vec3[i * arr->w + j];
    for (size_t i = 0; i < arr->h - 1; i++)
        for (size_t j = 0; j < arr->w - 1; j++) {
            new_arr.vec3[(i * 2 + 1) * new_arr.w + (j * 2 + 1)] =
            mid_triangle(new_arr.vec3[i * 2 * new_arr.w + j * 2],
            new_arr.vec3[(i + 1) * 2 * new_arr.w + j * 2],
            new_arr.vec3[i * 2 * new_arr.w + (j + 1) * 2]);
        }
    for (size_t i = 0; i < arr->h - 1; i++)
        for (size_t j = 0; j < arr->w - 1; j++) {
            new_arr.vec3[(i * 2 + 1) * new_arr.w + (j + 1) * 2] =
            mid_triangle(new_arr.vec3[(i * 2 + 1) * new_arr.w + (j * 2 + 1)],
            new_arr.vec3[i * 2 * new_arr.w + (j + 1) * 2],
            new_arr.vec3[(i + 1) * 2 * new_arr.w + (j + 1) * 2]);

            new_arr.vec3[(i + 1) * 2 * new_arr.w + j * 2 + 1] =
            mid_triangle(new_arr.vec3[(i * 2 + 1) * new_arr.w + (j * 2 + 1)],
            new_arr.vec3[(i + 1) * 2 * new_arr.w + (j + 1) * 2],
            new_arr.vec3[(i + 1) * 2 * new_arr.w + j * 2]);
        }
    for (size_t i = 0; i < arr->w - 1; i++)
        new_arr.vec3[i * 2 + 1] = vec3_divs(vec3_add(new_arr.vec3[i * 2], new_arr.vec3[(i + 1) * 2]), 2.0f);
    for (size_t i = 0; i < arr->h - 1; i++)
        new_arr.vec3[(i * 2 + 1) * new_arr.w] = vec3_divs(vec3_add(new_arr.vec3[i * 2 * new_arr.w], new_arr.vec3[(i + 1) * 2 * new_arr.w]), 2.0f);
    arr2d_vec3_destroy(*arr);
    *arr = new_arr;
}

static void send_ter_to_chunk(chunk_t *chunk, arr2d_vec3_t arr)
{
    for (size_t i = 0; i < arr.h - 1; i++)
        for (size_t j = 0; j < arr.w - 1; j++) {
            chunk_insert_rtx_triangle(chunk,
            rtx_triangle_create_discrete(arr.vec3[i * arr.w + j],
            arr.vec3[(i + 1) * arr.w + j], arr.vec3[i * arr.w + j + 1]));
            chunk_insert_rtx_triangle(chunk,
            rtx_triangle_create_discrete(arr.vec3[(i + 1) * arr.w + (j + 1)],
            arr.vec3[i * arr.w + j + 1], arr.vec3[(i + 1) * arr.w + j]));
        }
}

void chunk_gen_terrain(chunk_t *chunk)
{
    arr2d_vec3_t arr = arr2d_vec3_create(2, 2);
    vec3 base = {chunk->pos.x * CHUNK_SIZE, 0.0, chunk->pos.y * CHUNK_SIZE};

    arr.vec3[0] = base;
    arr.vec3[1] = vec3_add(base, (vec3){CHUNK_SIZE, 0.0, 0.0});
    arr.vec3[2] = vec3_add(base, (vec3){0.0, 0.0, CHUNK_SIZE});
    arr.vec3[3] = vec3_add(base, (vec3){CHUNK_SIZE, 0.0, CHUNK_SIZE});
    for (size_t i = 0; i < CHUNK_GEN_ITER; i++)
        split_ter(&arr);
    send_ter_to_chunk(chunk, arr);
    arr2d_vec3_destroy(arr);
}
