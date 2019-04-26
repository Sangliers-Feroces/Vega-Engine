/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static inter_ray3 world_inter(demo_t *demo, ray3 ray)
{
    return octree_intersect_ray_laxist(demo->world.tree, ray);
}

static int check_col(int do_laxist,
dvec3 pos, dvec3 *speed, dvec3 *avg_norm)
{
    inter_ray3 inter = world_inter(_demo, (ray3){pos, *speed});
    dvec3 p_in;
    dvec3 up = {0.0, 1.0, 0.0};
    dvec3 normal;

    if (inter.triangle == NULL)
        return 0;
    if (inter.min_t > (do_laxist ? 0.999 : 1.0))
        return 0;
    p_in = dvec3_add(pos, *speed);
    normal = dvec3_dot(inter.triangle->normal, up) > 0.8 ?
    up : inter.triangle->normal;
    inter = rtx_triangle_intersect_ray_no_cull(inter.triangle,
    (ray3){p_in, normal});
    if (inter.triangle == NULL)
        return 0;
    *speed = dvec3_add(*speed, dvec3_muls(dvec3_sub(inter.p, p_in), 1.0));
    *avg_norm = dvec3_add(*avg_norm, normal);
    return 1;
}

static void apply_disp(dvec3 *p, dvec3 disp)
{
    inter_ray3 inter = world_inter(_demo, (ray3){*p, disp});

    if ((inter.triangle == NULL) || (inter.min_t > 1.0)) {
        *p = dvec3_add(*p, disp);
        return;
    }
    *p = dvec3_add(inter.p, dvec3_muls(dvec3_normalize(disp), -0.005));
}

void entity3_physics(entity3 *ent)
{
    dvec3 speed_frame;
    dvec3 old_speed;
    dvec3 norm = {0.0, 0.0, 0.0};

    ent->trans.speed = dvec3_add(ent->trans.speed,
    dvec3_muls((dvec3){0.0, -9.8, 0.0}, _demo->win.framelen));
    speed_frame = dvec3_muls(ent->trans.speed, _demo->win.framelen);
    old_speed = speed_frame;
    for (size_t i = 0; i < 4; i++)
        if (!check_col(i > 0, ent->trans.pos, &speed_frame, &norm))
            break;
    dvec3 disp = dvec3_add(speed_frame,
    dvec3_muls(dvec3_normalize(norm), 0.005));
    apply_disp(&ent->trans.pos, disp);
    ent->trans.is_grounded = old_speed.y < speed_frame.y;
    ent->trans.speed = dvec3_divs(speed_frame, _demo->win.framelen);
}
