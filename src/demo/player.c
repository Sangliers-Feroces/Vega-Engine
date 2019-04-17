/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static inter_ray3 world_inter(demo_t *demo, ray3 ray)
{
    inter_ray3 inter = {NULL, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 0.0};

    for (size_t i = 0; i < demo->world.chunk_count; i++)
        octree_intersect_ray_laxist_iter(
        demo->world.chunk[i]->lod[WORLD_LOD_MAX].tree, ray, &inter);
    return inter;
}

static int check_col(demo_t *demo, dvec3 pos, dvec3 *speed, dvec3 *avg_norm)
{
    inter_ray3 inter = world_inter(demo, (ray3){pos, *speed});
    dvec3 p_in;
    dvec3 up = {0.0, 1.0, 0.0};
    dvec3 normal;

    if (inter.triangle == NULL)
        return 0;
    if (inter.min_t > 1.0f)
        return 0;
    p_in = dvec3_add(pos, *speed);
    normal = dvec3_dot(inter.triangle->normal, up) > 0.8 ?
    up : inter.triangle->normal;
    inter = rtx_triangle_intersect_ray_no_cull(inter.triangle,
    (ray3){p_in, normal});
    if (inter.triangle == NULL)
        return 0;
    *speed = dvec3_add(*speed, dvec3_muls(dvec3_sub(inter.p, p_in), 1.0));
    *avg_norm = normal;
    return 1;
}

static void slow_player_down(demo_t *demo)
{
    demo->player.speed.x *= 1.0 - demo->win.framelen * 6.0;
    demo->player.speed.z *= 1.0 - demo->win.framelen * 6.0;
}

static void cap_player_speed(dvec3 *speed)
{
    vec2 xz = {speed->x, speed->z};
    float dist = vec2_norm(xz);

    if (dist > PLAYER_MAX_SPEED) {
        xz = vec2_muls(xz, PLAYER_MAX_SPEED / dist);
        *speed = (dvec3){xz.x, speed->y, xz.y};
    }
}

static void apply_disp(demo_t *demo, dvec3 disp)
{
    inter_ray3 inter = world_inter(demo, (ray3){demo->player.pos, disp});

    if ((inter.triangle == NULL) || (inter.min_t > 1.0)) {
        demo->player.pos = dvec3_add(demo->player.pos, disp);
        return;
    }
    demo->player.pos = dvec3_add(inter.p, dvec3_muls(dvec3_normalize(disp), -0.005));
}

void player_physics(demo_t *demo)
{
    dvec3 speed_frame;
    dvec3 old_speed;
    dvec3 norm = {0.0, 0.0, 0.0};

    if (demo->player.is_grounded)
        slow_player_down(demo);
    demo->player.speed = dvec3_add(demo->player.speed,
    dvec3_muls((dvec3){0.0, -9.8, 0.0}, demo->win.framelen));
    cap_player_speed(&demo->player.speed);
    speed_frame = dvec3_muls(demo->player.speed, demo->win.framelen);
    old_speed = speed_frame;
    for (size_t i = 0; i < 4; i++)
        if (!check_col(demo, demo->player.pos, &speed_frame, &norm))
            break;
    dvec3 disp = dvec3_add(speed_frame, dvec3_muls(dvec3_normalize(norm), 0.005));
    apply_disp(demo, disp);
    demo->player.is_grounded = old_speed.y < speed_frame.y;
    demo->player.speed = dvec3_divs(speed_frame, demo->win.framelen);
    demo->cam.pos = dvec3_add(demo->player.pos, (dvec3){0.0, 1.75, 0.0});
}
