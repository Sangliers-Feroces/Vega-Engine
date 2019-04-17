/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** dungeons_gen
*/

#include "headers.h"

static dvec3 g_vertex_buffer_data[][3] = {
    {{-1.0f,-1.0f,-1.0f},
    {-1.0f,-1.0f, 1.0f},
    {-1.0f, 1.0f, 1.0f}},
    {{1.0f, 1.0f,-1.0f},
    {-1.0f,-1.0f,-1.0f},
    {-1.0f, 1.0f,-1.0f}},
    {{1.0f,-1.0f, 1.0f},
    {-1.0f,-1.0f,-1.0f},
    {1.0f,-1.0f,-1.0f}},
    {{1.0f, 1.0f,-1.0f},
    {1.0f,-1.0f,-1.0f},
    {-1.0f,-1.0f,-1.0f}},
    {{-1.0f,-1.0f,-1.0f},
    {-1.0f, 1.0f, 1.0f},
    {-1.0f, 1.0f,-1.0f}},
    {{1.0f,-1.0f, 1.0f},
    {-1.0f,-1.0f, 1.0f},
    {-1.0f,-1.0f,-1.0f}},
    {{-1.0f, 1.0f, 1.0f},
    {-1.0f,-1.0f, 1.0f},
    {1.0f,-1.0f, 1.0f}},
    {{1.0f, 1.0f, 1.0f},
    {1.0f,-1.0f,-1.0f},
    {1.0f, 1.0f,-1.0f}},
    {{1.0f,-1.0f,-1.0f},
    {1.0f, 1.0f, 1.0f},
    {1.0f,-1.0f, 1.0f}},
    {{1.0f, 1.0f, 1.0f},
    {1.0f, 1.0f,-1.0f},
    {-1.0f, 1.0f,-1.0f}},
    {{1.0f, 1.0f, 1.0f},
    {-1.0f, 1.0f,-1.0f},
    {-1.0f, 1.0f, 1.0f}},
    {{1.0f, 1.0f, 1.0f},
    {-1.0f, 1.0f, 1.0f},
    {1.0f,-1.0f, 1.0f}}
};

static dvec3 dungeon_point_scaling(dvec3 point, int scaling_x, int scaling_y, int scaling_z)
{
    dvec3 res = (dvec3){point.x, point.y, point.z};

    if (res.x > _dungeons.cur_origin.x)
        res.x += scaling_x;
    if (res.y > _dungeons.cur_origin.y)
        res.y += scaling_y;
    if (res.z > _dungeons.cur_origin.z)
        res.z += scaling_z;
    return res;
}

static void dungeon_insert_in_world(demo_t *demo, vec_rtx_triangle *rooms, int nb_rooms)
{
    for (int i = 0; i < nb_rooms; i++) {
        world_insert_vec_rtx_triangle(demo, rooms[i]);
    }
}

static vec_rtx_triangle dungeons_gen_room(void)
{
    vec_rtx_triangle room = vec_rtx_triangle_create();
    dvec3 cur_triangle[3];

    dungeons_set_next_origin();
    for (int i = 0; i < 12; i++) {
        cur_triangle[1] = dungeon_point_scaling(g_vertex_buffer_data[i][0], 5, 2, 3);
        cur_triangle[0] = dungeon_point_scaling(g_vertex_buffer_data[i][1], 5, 2, 3);
        cur_triangle[2] = dungeon_point_scaling(g_vertex_buffer_data[i][2], 5, 2, 3);
        vec_rtx_triangle_add(&room, rtx_triangle_create(cur_triangle));
    }
    return room;
}

void dungeons_gen_all(demo_t *demo, size_t rooms_limit)
{
    vec_rtx_triangle *rooms;
    int generated_rooms = get_random_int(1, rooms_limit);

    printf("generated rooms : %d\n", generated_rooms);
    rooms = (vec_rtx_triangle *)malloc_safe(sizeof(vec_rtx_triangle) *
    generated_rooms);
    for (int i = 0; i < generated_rooms; i++)
        rooms[i] = dungeons_gen_room();
    dungeon_insert_in_world(demo, rooms, generated_rooms);
    for (int i = 0; i < generated_rooms; i++)
        vec_rtx_triangle_free(&rooms[i]);
    free(rooms);
    return;
}
