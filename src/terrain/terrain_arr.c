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

static int get_point(arr2d_dvec3_t arr, ssize2 p, dvec3 *res)
{
    if ((p.x >= 0) && (p.x < (ssize_t)arr.w) &&
    (p.y >= 0) && (p.y < (ssize_t)arr.h)) {
        *res = arr.dvec3[p.y * arr.w + p.x];
        return 1;
    } else
        return 0;
}

static dvec3 get_normal(arr2d_dvec3_t arr, ssize2 p)
{
    dvec3 acc = {0.0, 0.0, 0.0};
    size_t count = 0;
    ssize2 around[4][3] = {{{0, 0}, {0, 1}, {1, 0}},
    {{0, 0}, {0, -1}, {-1, 0}}, {{0, 0}, {1, 0}, {0, -1}},
    {{0, 0}, {0, -1}, {1, 0}}};
    dvec3 t[3] = {acc, acc, acc};
    int do_continue;

    for (size_t i = 0; i < 4; i++) {
        do_continue = 0;
        for (size_t j = 0; j < 3; j++)
            if (!get_point(arr, ssize2_add(p, around[i][j]), &t[j]))
                do_continue = 1;
        if (do_continue)
            continue;
        acc = dvec3_add(acc, dnormal3(t[0], t[1], t[2]));
        count++;
    }
    if (count == 0)
        return dvec3_init(FLT64_INF, FLT64_INF, FLT64_INF);
    else
        return dvec3_normalize(acc);
}

static arr2d_dvec3_t gen_normals(arr2d_dvec3_t arr)
{
    arr2d_dvec3_t res = arr2d_dvec3_create(arr.w, arr.h);

    for (size_t i = 0; i < res.h; i++)
        for (size_t j = 0; j < res.w; j++)
            res.dvec3[i * res.w + j] = get_normal(arr, (ssize2){j, i});
    return res;
}

static dvec3 get_normal_from_triangle(arr2d_dvec3_t arr, ssize2 base, ssize2 *off)
{
    dvec3 p[3];
    ssize2 ndx;

    for (size_t i = 0; i < 3; i++) {
        ndx = ssize2_add(base, off[i]);
        p[i] = arr.dvec3[ndx.y * arr.w + ndx.x];
    }
    return dnormal3(p[0], p[1], p[2]);
}

static void send_ter_to_chunk_lod_gen(chunk_t *chunk, size_t lod, arr2d_dvec3_t arr, arr2d_dvec3_t normals, dvec3 chunk_rel, srect area)
{
    mesh_full_t *mesh;
    vec2 uv[3] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 1.0f}};
    ssize2 off[2][3] = {{{0, 0}, {0, 1}, {1, 0}}, {{1, 1}, {1, 0}, {0, 1}}};
    ssize2 ndx;
    ssize2 ndx_off;
    vec3 base = {0.0, -42.0f, 0.0};
    vec3 sq[4];
    vec3 pos;
    vec3 norm;

    if (chunk->terrain == NULL) {
        chunk->terrain = chunk_add_entity(chunk);
        chunk->terrain->tag = ENTITY3_TAG_TERRAIN;
    }
    if (chunk->terrain->render[lod].mesh.m != NULL)
        return;
    mesh = entity3_create_render(chunk->terrain, lod, MATERIAL_GRASS, 0);
    for (ssize_t i = 0; i < area.s.y - 1; i++)
        for (ssize_t j = 0; j < area.s.x - 1; j++) {
            for (size_t k = 0; k < 2; k++) {
                for (size_t l = 0; l < 3; l++) {
                    ndx = ssize2_add(area.p, (ssize2){j, i});
                    ndx_off = ssize2_add(ndx, off[k][l]);
                    pos = dvec3_vec3(dvec3_sub(arr.dvec3[ndx_off.y * arr.w + ndx_off.x], chunk_rel));
                    norm = dvec3_vec3(normals.dvec3[ndx_off.y * normals.w + ndx_off.x]);
                    if (norm.x == FLT64_INF)
                        norm = dvec3_vec3(get_normal_from_triangle(arr, ndx, off[k]));
                    mesh_add_vertex(mesh->mesh, vertex_init(pos, norm, uv[l]));
                }
            }
        }
    if (lod == 1) {
        chunk->terrain_base = arr2d_dvec3_copy_rect(arr, area);
        arr2d_dvec3_sub(chunk->terrain_base, chunk_rel);
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

static void send_ter_to_chunk_lod(size_t lod, arr2d_dvec3_t arr, arr2d_dvec3_t normals,
srect area, ssize2 chunk_pos, ssize2 iter)
{
    chunk_t *chunk = world_chunk_get_adv(chunk_pos, 0, 0);
    dvec3 chunk_rel = dvec3_init(iter.x * CHUNK_SIZE, 0.0, iter.y * CHUNK_SIZE);

    send_ter_to_chunk_lod_gen(chunk, lod, arr, normals, chunk_rel, area);
}

static void send_ter_to_chunks_lod(size_t lod, arr2d_dvec3_t arr, arr2d_dvec3_t normals, ssize2 pos)
{
    ssize2 pos_first_chunk = ssize2_muls(pos, CHUNK_TERRAIN_SUB_SIZE);
    ssize_t step = (arr.w - 1) / CHUNK_TERRAIN_SUB_SIZE;

    for (size_t i = 0; i < CHUNK_TERRAIN_SUB_SIZE; i++)
        for (size_t j = 0; j < CHUNK_TERRAIN_SUB_SIZE; j++)
            send_ter_to_chunk_lod(lod, arr, normals, (srect){{j * step, i * step}, {step + 1, step + 1}},
            ssize2_add(pos_first_chunk, (ssize2){j, i}), (ssize2){j, i});
}

static void send_iter_to_ter_border(arr2d_dvec3_t arr, size_t ndx, ssize2 pos)
{
    ssize2 pos_first_chunk = ssize2_muls(pos, CHUNK_TERRAIN_SUB_SIZE);
    chunk_t *chunk = world_chunk_get_adv(pos_first_chunk, 0, 0);

    for (size_t i = 0; i < 2; i++) {
        chunk->border_ter.data[1][i][ndx] = arr_dvec3_create(arr.w);
        chunk->border_ter.data[0][i][ndx] = arr_dvec3_create(arr.h);
    }
    for (size_t i = 0; i < arr.h; i++) {
        chunk->border_ter.data[0][0][ndx].dvec3[i] = arr.dvec3[i * arr.w];
        chunk->border_ter.data[0][1][ndx].dvec3[i] = arr.dvec3[i * arr.w + arr.w - 1];
    }
    for (size_t i = 0; i < arr.w; i++) {
        chunk->border_ter.data[1][0][ndx].dvec3[i] = arr.dvec3[i];
        chunk->border_ter.data[1][1][ndx].dvec3[i] = arr.dvec3[(arr.h - 1) * arr.w + i];
    }
}

static void send_iter_to_chunk_border(chunk_t *chunk, arr2d_dvec3_t arr, size_t ndx)
{
    for (size_t i = 0; i < 2; i++) {
        chunk->border.data[1][i][ndx] = arr_dvec3_create(arr.w);
        chunk->border.data[0][i][ndx] = arr_dvec3_create(arr.h);
    }
    for (size_t i = 0; i < arr.h; i++) {
        chunk->border.data[0][0][ndx].dvec3[i] = arr.dvec3[i * arr.w];
        chunk->border.data[0][1][ndx].dvec3[i] = arr.dvec3[i * arr.w + arr.w - 1];
    }
    for (size_t i = 0; i < arr.w; i++) {
        chunk->border.data[1][0][ndx].dvec3[i] = arr.dvec3[i];
        chunk->border.data[1][1][ndx].dvec3[i] = arr.dvec3[(arr.h - 1) * arr.w + i];
    }
}

static void apply_constraints(arr2d_dvec3_t arr, chunk_border_t border,
size_t ndx)
{
    if (border.data[0][0][ndx].count > 0)
        for (size_t i = 0; i < arr.h; i++)
            arr.dvec3[i * arr.w] = border.data[0][0][ndx].dvec3[i];
    if (border.data[0][1][ndx].count > 0)
        for (size_t i = 0; i < arr.h; i++)
            arr.dvec3[i * arr.w + arr.w - 1] = border.data[0][1][ndx].dvec3[i];
    if (border.data[1][0][ndx].count > 0)
        for (size_t i = 0; i < arr.w; i++)
            arr.dvec3[i] = border.data[1][0][ndx].dvec3[i];
    if (border.data[1][1][ndx].count > 0)
        for (size_t i = 0; i < arr.w; i++)
            arr.dvec3[(arr.h - 1) * arr.w + i] = border.data[1][1][ndx].dvec3[i];
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
    chunk_border_t border = chunk_border_ter_fetch(ter_pos);
    arr2d_dvec3_t n;

    arr.dvec3[0] = base;
    arr.dvec3[1] = dvec3_add(base, (dvec3){CHUNK_SIZE_TERRAIN, 0.0, 0.0});
    arr.dvec3[2] = dvec3_add(base, (dvec3){0.0, 0.0, CHUNK_SIZE_TERRAIN});
    arr.dvec3[3] = dvec3_add(base, (dvec3){CHUNK_SIZE_TERRAIN, 0.0,
    CHUNK_SIZE_TERRAIN});
    for (size_t i = 0; i < CHUNK_GEN_ITER; i++) {
        split_ter(&arr, stren);
        apply_constraints(arr, border, i);
        send_iter_to_ter_border(arr, i, ter_pos);
        switch (i) {
        case 4:
            n = gen_normals(arr);
            send_ter_to_chunks_lod(0, arr, n, ter_pos);
            arr2d_dvec3_destroy(n);
            break;
        case 5:
            n = gen_normals(arr);
            send_ter_to_chunks_lod(1, arr, n, ter_pos);
            arr2d_dvec3_destroy(n);
            break;
        }
    }
    arr2d_dvec3_destroy(arr);
    chunk_border_destroy(border);
}

void chunk_detail_terrain(chunk_t *chunk)
{
    arr2d_dvec3_t arr = arr2d_dvec3_copy(chunk->terrain_base);
    dvec3 chunk_rel = dvec3_init(0.0, 0.0, 0.0);
    chunk_border_t border = chunk_border_fetch(chunk->pos);
    arr2d_dvec3_t n;

    for (size_t i = 0; i < CHUNK_GEN_EXT_ITER; i++) {
        split_ter(&arr, 0.05 / (i + 1));
        apply_constraints(arr, border, i);
        send_iter_to_chunk_border(chunk, arr, i);
        switch (i) {
        case 1:
            n = gen_normals(arr);
            send_ter_to_chunk_lod_gen(chunk, WORLD_LOD_MAX, arr, n, chunk_rel, (srect){{0, 0}, {arr.w, arr.h}});
            arr2d_dvec3_destroy(n);
            break;
        }
    }
    arr2d_dvec3_destroy(arr);
    chunk_border_destroy(border);
    entity3_bind_col(chunk->terrain, chunk->terrain->render[WORLD_LOD_MAX].mesh);
}
