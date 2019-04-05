/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** dungeons_gen
*/

#include "headers.h"

static vec3 g_vertex_buffer_data[][3] = {
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

static void dungeon_insert_in_world(demo_t *demo, vec_rtx_triangle *rooms, int nb_rooms)
{
    for (int i = 0; i < nb_rooms; i++) {
        world_insert_vec_rtx_triangle(demo, rooms[i]);
    }
}

static vec_rtx_triangle dungeons_gen_room(void)
{
    vec_rtx_triangle room = vec_rtx_triangle_create();
    vec3 cur_triangle[3];

    for (int i = 0; i < 12; i++) {
        cur_triangle[1] = g_vertex_buffer_data[i][0];
        cur_triangle[0] = g_vertex_buffer_data[i][1];
        cur_triangle[2] = g_vertex_buffer_data[i][2];
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
    return;
}
