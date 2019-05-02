/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

inter_ray3 world_inter(ray3 ray)
{
    return octree_intersect_ray(_demo->world.tree, ray);
}

inter_ray3 world_inter_laxist(ray3 ray)
{
    return octree_intersect_ray_laxist(_demo->world.tree, ray);
}

inter_ray3 world_inter_laxist_fast(ray3 ray)
{
    return octree_intersect_ray_laxist_fast(_demo->world.tree, ray);
}

static int check_col(int do_fast, int do_laxist,
dvec3 pos, dvec3 *speed, dvec3 *avg_norm, double slide)
{
    inter_ray3 inter = do_fast ? world_inter_laxist_fast((ray3){pos, *speed}) :
    world_inter_laxist((ray3){pos, *speed});
    dvec3 p_in;
    dvec3 up = {0.0, 1.0, 0.0};
    dvec3 normal;

    if (inter.triangle == NULL)
        return 0;
    if (inter.min_t > (do_laxist ? 0.999 : 1.0))
        return 0;
    p_in = dvec3_add(pos, *speed);
    normal = dvec3_dot(inter.triangle->normal, up) > slide ?
    up : inter.triangle->normal;
    inter = rtx_triangle_intersect_ray_no_cull(inter.triangle,
    (ray3){p_in, normal});
    if (inter.triangle == NULL)
        return 0;
    *speed = dvec3_add(*speed, dvec3_muls(dvec3_sub(inter.p, p_in), 1.0));
    *avg_norm = dvec3_add(*avg_norm, normal);
    return 1;
}

static void apply_disp(int do_fast, dvec3 *p, dvec3 disp)
{
    inter_ray3 inter = do_fast ? world_inter_laxist_fast((ray3){*p, disp}) :
    world_inter_laxist((ray3){*p, disp});

    if ((inter.triangle == NULL) || (inter.min_t > 1.0)) {
        *p = dvec3_add(*p, disp);
        return;
    }
    *p = dvec3_add(inter.p, dvec3_muls(dvec3_normalize(disp), -0.001));
}

static void slow_ent_down(entity3 *ent)
{
    ent->trans.speed.x *= 1.0 - _demo->win.framelen * 2.0;
    ent->trans.speed.z *= 1.0 - _demo->win.framelen * 2.0;
}

void entity3_physics(entity3 *ent)
{
    dvec3 speed_frame;
    dvec3 old_speed;
    dvec3 norm = {0.0, 0.0, 0.0};
    dvec3 p = dmat4_trans(ent->trans.world);
    int is_underwater = dmat4_trans(ent->trans.world).y < -42.0;
    int do_fast = ent->tag != ENTITY3_TAG_PLAYER;

    ent->trans.speed = dvec3_add(ent->trans.speed,
    dvec3_muls((dvec3){0.0, !is_underwater ?
    -9.8 : -1.0, 0.0}, _demo->win.framelen));
    if (is_underwater)
        slow_ent_down(ent);
    speed_frame = dvec3_muls(ent->trans.speed, _demo->win.framelen);
    old_speed = speed_frame;
    for (size_t i = 0; i < 4; i++)
        if (!check_col(do_fast, i > 0, p, &speed_frame, &norm,
        ent->trans.slide_threshold))
            break;
    dvec3 disp = dvec3_add(speed_frame,
    dvec3_muls(dvec3_normalize(norm), 0.001));
    apply_disp(do_fast, &p, disp);
    entity3_update_trans_inv(ent->root);
    ent->trans.pos = dmat4_mul_dvec3(ent->root->trans.world_inv, p);
    ent->trans.is_grounded = old_speed.y < speed_frame.y;
    ent->trans.speed = dvec3_divs(speed_frame, _demo->win.framelen);
    if (ent->trans.pos.y < -512.0)
        entity3_set_on_ground(ent);
}
