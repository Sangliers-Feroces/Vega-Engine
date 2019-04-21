/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static dvec3 mid_triangle(dvec3 a, dvec3 b, dvec3 c, double stren)
{
    double dist = dvec3_dist(b, c);
    dvec3 normal = dnormal3(a, b, c);
    dvec3 mid = dvec3_add(
    dvec3_divs(dvec3_add(b, c), 2.0),
    dvec3_muls(normal, (randf() - 0.5) * dist * stren));

    return mid;
}

static void split_ter(arr2d_dvec3_t *arr, double stren)
{
    arr2d_dvec3_t new_arr = arr2d_dvec3_create(arr->w * 2 - 1, arr->h * 2 - 1);

    for (size_t i = 0; i < arr->h; i++)
        for (size_t j = 0; j < arr->w; j++)
            new_arr.dvec3[i * 2 * new_arr.w + j * 2] = arr->dvec3[i * arr->w + j];
    for (size_t i = 0; i < arr->h - 1; i++)
        for (size_t j = 0; j < arr->w - 1; j++) {
            new_arr.dvec3[(i * 2 + 1) * new_arr.w + (j * 2 + 1)] =
            mid_triangle(new_arr.dvec3[i * 2 * new_arr.w + j * 2],
            new_arr.dvec3[(i + 1) * 2 * new_arr.w + j * 2],
            new_arr.dvec3[i * 2 * new_arr.w + (j + 1) * 2], stren);
        }
    for (size_t i = 0; i < arr->h - 1; i++)
        for (size_t j = 0; j < arr->w - 1; j++) {
            new_arr.dvec3[(i * 2 + 1) * new_arr.w + (j + 1) * 2] =
            mid_triangle(new_arr.dvec3[(i * 2 + 1) * new_arr.w + (j * 2 + 1)],
            new_arr.dvec3[i * 2 * new_arr.w + (j + 1) * 2],
            new_arr.dvec3[(i + 1) * 2 * new_arr.w + (j + 1) * 2], stren);

            new_arr.dvec3[(i + 1) * 2 * new_arr.w + j * 2 + 1] =
            mid_triangle(new_arr.dvec3[(i * 2 + 1) * new_arr.w + (j * 2 + 1)],
            new_arr.dvec3[(i + 1) * 2 * new_arr.w + (j + 1) * 2],
            new_arr.dvec3[(i + 1) * 2 * new_arr.w + j * 2], stren);
        }
    for (size_t i = 0; i < arr->w - 1; i++)
        new_arr.dvec3[i * 2 + 1] = dvec3_divs(dvec3_add(new_arr.dvec3[i * 2], new_arr.dvec3[(i + 1) * 2]), 2.0);
    for (size_t i = 0; i < arr->h - 1; i++)
        new_arr.dvec3[(i * 2 + 1) * new_arr.w] = dvec3_divs(dvec3_add(new_arr.dvec3[i * 2 * new_arr.w], new_arr.dvec3[(i + 1) * 2 * new_arr.w]), 2.0);
    arr2d_dvec3_destroy(*arr);
    *arr = new_arr;
}

static void send_ter_to_chunk_lod(chunk_t *chunk, entity3 *ent, size_t lod,
arr2d_dvec3_t arr)
{
    mesh_full_t *mesh;
    vec3 base = {0.0, -42.0f, 0.0};
    vec3 sq[4];
    vec3 pos[3];
    vec2 uv[3] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 1.0f}};

    sq[0] = base;
    sq[1] = vec3_add(base, (vec3){CHUNK_SIZE, 0.0f, 0.0f});
    sq[2] = vec3_add(base, (vec3){0.0f, 0.0f, CHUNK_SIZE});
    sq[3] = vec3_add(base, (vec3){CHUNK_SIZE, 0.0f, CHUNK_SIZE});
    mesh = entity3_create_render(ent, lod, MATERIAL_GRASS, 0);
    for (size_t i = 0; i < arr.h - 1; i++)
        for (size_t j = 0; j < arr.w - 1; j++) {
            pos[0] = dvec3_vec3(arr.dvec3[i * arr.w + j]);
            pos[1] = dvec3_vec3(arr.dvec3[(i + 1) * arr.w + j]);
            pos[2] = dvec3_vec3(arr.dvec3[i * arr.w + j + 1]);
            mesh_add_triangle_pos_uv(mesh->mesh, pos, uv);
            pos[0] = dvec3_vec3(arr.dvec3[(i + 1) * arr.w + (j + 1)]);
            pos[1] = dvec3_vec3(arr.dvec3[i * arr.w + j + 1]);
            pos[2] = dvec3_vec3(arr.dvec3[(i + 1) * arr.w + j]);
            mesh_add_triangle_pos_uv(mesh->mesh, pos, uv);
        }
    entity3 *water = chunk_add_entity(chunk);
    mesh = entity3_create_render(water, 0, MATERIAL_WATER, 0);

    mesh_add_triangle_pos_uv(mesh->mesh, (vec3[]){sq[0], sq[2], sq[1]}, uv);
    mesh_add_triangle_pos_uv(mesh->mesh, (vec3[]){sq[3], sq[1], sq[2]}, uv);
}

static void send_iter_to_border(chunk_t *chunk, arr2d_dvec3_t arr, size_t ndx)
{
    for (size_t i = 0; i < 2; i++) {
        chunk->border.hor[ndx][i] = arr_dvec3_create(arr.w);
        chunk->border.ver[ndx][i] = arr_dvec3_create(arr.h);
    }
    for (size_t i = 0; i < arr.h; i++) {
        chunk->border.hor[ndx][0].dvec3[i] = arr.dvec3[i * arr.w];
        chunk->border.hor[ndx][1].dvec3[i] = arr.dvec3[i * arr.w + arr.w - 1];
    }
    for (size_t i = 0; i < arr.w; i++) {
        chunk->border.ver[ndx][0].dvec3[i] = arr.dvec3[i];
        chunk->border.ver[ndx][1].dvec3[i] = arr.dvec3[(arr.h - 1) * arr.w + i];
    }
}

static void apply_constraints(arr2d_dvec3_t arr, chunk_border_t border,
size_t ndx)
{
    for (size_t i = 0; i < arr.h; i++) {
        if (border.hor[ndx][0].dvec3 != NULL)
            arr.dvec3[i * arr.w] = border.hor[ndx][0].dvec3[i];
        if (border.hor[ndx][1].dvec3 != NULL)
            arr.dvec3[i * arr.w + arr.w - 1] = border.hor[ndx][1].dvec3[i];
    }
    for (size_t i = 0; i < arr.w; i++) {
        if (border.ver[ndx][0].dvec3 != NULL)
            arr.dvec3[i] = border.ver[ndx][0].dvec3[i];
        if (border.ver[ndx][1].dvec3 != NULL)
            arr.dvec3[(arr.h - 1) * arr.w + i] = border.ver[ndx][1].dvec3[i];
    }
}

double cos_der(double value)
{
    return 0.2 + 0.8 * ((sin(value / 3.0) + 1.0) / 2.5);
}

static double get_strength(ssize2 pos)
{
    return (cos_der(pos.x) * cos_der(pos.y)) / 2.0;
}

void chunk_gen_terrain(chunk_t *chunk, entity3 *ent)
{
    arr2d_dvec3_t arr = arr2d_dvec3_create(2, 2);
    double stren = get_strength(chunk->pos);
    dvec3 base = {0.0, (stren - 0.25) * 384.0, 0.0};
    chunk_border_t border = chunk_border_fetch(chunk->pos);

    arr.dvec3[0] = base;
    arr.dvec3[1] = dvec3_add(base, (dvec3){CHUNK_SIZE, 0.0, 0.0});
    arr.dvec3[2] = dvec3_add(base, (dvec3){0.0, 0.0, CHUNK_SIZE});
    arr.dvec3[3] = dvec3_add(base, (dvec3){CHUNK_SIZE, 0.0, CHUNK_SIZE});
    for (size_t i = 0; i < CHUNK_GEN_ITER; i++) {
        split_ter(&arr, stren);
        apply_constraints(arr, border, i);
        send_iter_to_border(chunk, arr, i);
        switch (i) {
        case 3:
            send_ter_to_chunk_lod(chunk, ent, 0, arr);
            break;
        case 4:
            send_ter_to_chunk_lod(chunk, ent, 1, arr);
            break;
        case 5:
            send_ter_to_chunk_lod(chunk, ent, 2, arr);
            break;
        }
    }
    arr2d_dvec3_destroy(arr);
    chunk_border_destroy(border);
}
