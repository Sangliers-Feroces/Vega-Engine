/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static inter_ray3 world_inter(demo_t *demo, ray3 ray)
{
    inter_ray3 inter = {NULL, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, 0.0f};

    for (size_t i = 0; i < demo->world.chunk_count; i++)
        octree_intersect_ray_laxist_iter(
        demo->world.chunk[i]->lod[WORLD_LOD_MAX].tree, ray, &inter);
    return inter;
}

static void check_col(demo_t *demo, vec3 pos, vec3 *speed)
{
    inter_ray3 inter = world_inter(demo, (ray3){pos, *speed});
    vec3 p_in;
    vec3 up = {0.0f, 1.0f, 0.0f};

    if (inter.triangle == NULL)
        return;
    if (inter.min_t > 1.0f)
        return;
    p_in = vec3_add(pos, *speed);
    inter = rtx_triangle_intersect_ray_no_cull(inter.triangle,
    (ray3){p_in, vec3_dot(inter.triangle->normal, up) > 0.5f ?
    up : inter.triangle->normal});
    if (inter.triangle == NULL)
        return;
    *speed = vec3_add(*speed, vec3_muls(vec3_sub(inter.p, p_in), 1.0f));
}

static void slow_player_down(demo_t *demo)
{
    demo->player.speed.x *= 1.0f - demo->win.framelen * 6.0f;
    demo->player.speed.z *= 1.0f - demo->win.framelen * 6.0f;
}

static void cap_player_speed(vec3 *speed)
{
    vec2 xz = {speed->x, speed->z};
    float dist = vec2_norm(xz);

    if (dist > PLAYER_MAX_SPEED) {
        xz = vec2_muls(xz, PLAYER_MAX_SPEED / dist);
        *speed = (vec3){xz.x, speed->y, xz.y};
    }
}

void player_physics(demo_t *demo)
{
    vec3 speed_frame;
    vec3 old_speed;

    if (demo->player.is_grounded)
        slow_player_down(demo);
    demo->player.speed = vec3_add(demo->player.speed,
    vec3_muls((vec3){0.0f, -9.8f, 0.0f}, demo->win.framelen));
    cap_player_speed(&demo->player.speed);
    speed_frame = vec3_muls(demo->player.speed, demo->win.framelen);
    old_speed = speed_frame;
    for (size_t i = 0; i < 4; i++)
        check_col(demo, demo->player.pos, &speed_frame);
    demo->player.pos = vec3_add(demo->player.pos, speed_frame);
    demo->player.is_grounded = old_speed.y < speed_frame.y;
    demo->player.speed = vec3_divs(speed_frame, demo->win.framelen);
    demo->player.pos = vec3_add(demo->player.pos,
    vec3_muls(vec3_normalize(vec3_sub(speed_frame, old_speed)), 0.01f));
    demo->cam.pos = vec3_add(demo->player.pos, (vec3){0.0f, 1.75f, 0.0f});
}
