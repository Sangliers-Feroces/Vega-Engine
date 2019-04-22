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

static void send_ter_to_chunk_lod(size_t lod, arr2d_dvec3_t arr,
srect area, ssize2 chunk_pos, ssize2 iter)
{
    chunk_t *chunk = world_chunk_get_adv(_demo, chunk_pos, 0, 0);
    mesh_full_t *mesh;
    vec2 uv[3] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 1.0f}};
    vec3 base = {0.0, -42.0f, 0.0};
    vec3 sq[4];
    vec3 pos[3];
    dvec3 chunk_rel = dvec3_init(iter.x * CHUNK_SIZE, 0.0, iter.y * CHUNK_SIZE);

    mesh = entity3_create_render(chunk->terrain, lod, MATERIAL_GRASS, 0);
    for (ssize_t i = 0; i < area.s.y - 1; i++)
        for (ssize_t j = 0; j < area.s.x - 1; j++) {
            pos[0] = dvec3_vec3(dvec3_sub(arr.dvec3[(area.p.y + i) * arr.w + area.p.x + j], chunk_rel));
            pos[1] = dvec3_vec3(dvec3_sub(arr.dvec3[(area.p.y + i + 1) * arr.w + area.p.x + j], chunk_rel));
            pos[2] = dvec3_vec3(dvec3_sub(arr.dvec3[(area.p.y + i) * arr.w + area.p.x + j + 1], chunk_rel));
            mesh_add_triangle_pos_uv(mesh->mesh, pos, uv);
            pos[0] = dvec3_vec3(dvec3_sub(arr.dvec3[(area.p.y + i + 1) * arr.w + (area.p.x + j + 1)], chunk_rel));
            pos[1] = dvec3_vec3(dvec3_sub(arr.dvec3[(area.p.y + i) * arr.w + area.p.x + j + 1], chunk_rel));
            pos[2] = dvec3_vec3(dvec3_sub(arr.dvec3[(area.p.y + i + 1) * arr.w + area.p.x + j], chunk_rel));
            mesh_add_triangle_pos_uv(mesh->mesh, pos, uv);
        }
    if ((lod == 1) && (chunk->terrain->col.mesh.m == NULL)) {
        entity3_update(chunk->ents);
        entity3_bind_col(chunk->terrain,
        entity3_get_lod_ref(chunk->terrain, 1));
    }
    if (lod > 0)
        return;
    sq[0] = base;
    sq[1] = vec3_add(base, (vec3){CHUNK_SIZE, 0.0f, 0.0f});
    sq[2] = vec3_add(base, (vec3){0.0f, 0.0f, CHUNK_SIZE});
    sq[3] = vec3_add(base, (vec3){CHUNK_SIZE, 0.0f, CHUNK_SIZE});
    entity3 *water = chunk_add_entity(chunk);
    mesh = entity3_create_render(water, 0, MATERIAL_WATER, 0);
    mesh_add_triangle_pos_uv(mesh->mesh, (vec3[]){sq[0], sq[2], sq[1]}, uv);
    mesh_add_triangle_pos_uv(mesh->mesh, (vec3[]){sq[3], sq[1], sq[2]}, uv);
}

static void send_ter_to_chunks_lod(size_t lod, arr2d_dvec3_t arr, ssize2 pos)
{
    ssize2 pos_first_chunk = ssize2_muls(pos, CHUNK_TERRAIN_SUB_SIZE);
    ssize_t step = (arr.w - 1) / CHUNK_TERRAIN_SUB_SIZE;

    for (size_t i = 0; i < CHUNK_TERRAIN_SUB_SIZE; i++)
        for (size_t j = 0; j < CHUNK_TERRAIN_SUB_SIZE; j++)
            send_ter_to_chunk_lod(lod, arr, (srect){{j * step, i * step}, {step + 1, step + 1}},
            ssize2_add(pos_first_chunk, (ssize2){j, i}), (ssize2){j, i});
}

static void send_iter_to_border(arr2d_dvec3_t arr, size_t ndx, srect area, ssize2 pos)
{
    chunk_t *chunk = world_chunk_get_adv(_demo, pos, 0, 0);

    if (ndx == 0) {
        chunk->terrain = chunk_add_entity(chunk);
        chunk->terrain->tag = ENTITY3_TAG_TERRAIN;
    }
    for (size_t i = 0; i < 2; i++) {
        chunk->border.hor[ndx][i] = arr_dvec3_create(area.s.y);
        chunk->border.ver[ndx][i] = arr_dvec3_create(area.s.x);
    }
    for (ssize_t i = 0; i < area.s.y; i++) {
        chunk->border.hor[ndx][0].dvec3[i] = arr.dvec3[(area.p.y + i) * arr.w + area.p.x];
        chunk->border.hor[ndx][1].dvec3[i] = arr.dvec3[(area.p.y + i) * arr.w + area.p.x + area.s.x - 1];
    }
    for (ssize_t i = 0; i < area.s.x; i++) {
        chunk->border.ver[ndx][0].dvec3[i] = arr.dvec3[area.p.y * arr.w + area.p.x + i];
        chunk->border.ver[ndx][1].dvec3[i] = arr.dvec3[(area.p.y + area.s.y - 1) * arr.w + area.p.x + i];
    }
}

static void send_iter_to_borders(arr2d_dvec3_t arr, size_t ndx, ssize2 pos)
{
    ssize2 pos_first_chunk = ssize2_muls(pos, CHUNK_TERRAIN_SUB_SIZE);
    ssize_t step = (arr.w - 1) / CHUNK_TERRAIN_SUB_SIZE;

    for (size_t i = 0; i < CHUNK_TERRAIN_SUB_SIZE; i++)
        for (size_t j = 0; j < CHUNK_TERRAIN_SUB_SIZE; j++)
            send_iter_to_border(arr, ndx, (srect){{j * step, i * step}, {step + 1, step + 1}},
            ssize2_add(pos_first_chunk, (ssize2){j, i}));
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

void chunk_gen_terrain(ssize2 pos)
{
    ssize2 ter_pos = chunk_get_terrain_pos(pos);
    arr2d_dvec3_t arr = arr2d_dvec3_create(2, 2);
    double stren = get_strength(ter_pos);
    dvec3 base = {0.0, (stren - 0.25) * 384.0, 0.0};
    chunk_border_t border = chunk_border_fetch(ter_pos);

    arr.dvec3[0] = base;
    arr.dvec3[1] = dvec3_add(base, (dvec3){CHUNK_SIZE_TERRAIN, 0.0, 0.0});
    arr.dvec3[2] = dvec3_add(base, (dvec3){0.0, 0.0, CHUNK_SIZE_TERRAIN});
    arr.dvec3[3] = dvec3_add(base, (dvec3){CHUNK_SIZE_TERRAIN, 0.0,
    CHUNK_SIZE_TERRAIN});
    for (size_t i = 0; i < CHUNK_GEN_ITER; i++) {
        split_ter(&arr, stren);
        apply_constraints(arr, border, i);
        send_iter_to_borders(arr, i, ter_pos);
        switch (i) {
        case 4:
            send_ter_to_chunks_lod(0, arr, ter_pos);
            break;
        case 5:
            send_ter_to_chunks_lod(1, arr, ter_pos);
            break;
        }
    }
    arr2d_dvec3_destroy(arr);
    chunk_border_destroy(border);
}
