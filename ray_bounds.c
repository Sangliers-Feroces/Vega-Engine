/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** optiiiiiii rtx
*/

#include "headers.h"

static int ray1d_bound_inside(ray1 r, float min, float max, vec2 *t)
{
    if (r.v > 0.0f) {
        t->x = MAX(t->x, 0.0f);
        t->y = MIN(t->y, (max - r.p) / r.v);
    } else {
        t->x = MAX(t->x, (min - r.p) / r.v);
        t->y = MIN(t->y, 0.0f);
    }
    return 1;
}

static int ray1d_bound(ray1 r, float min, float max, vec2 *t)
{
    if (r.v == 0.0f)
        return ((r.p >= min) && (r.p < max));
    if (r.p < min) {
        if (r.v > 0.0f) {
            t->x = MAX(t->x, (min - r.p) / r.v);
            t->y = MIN(t->y, (max - r.p) / r.v);
            return 1;
        } else
            return 0;
    } else if (r.p >= max) {
        if (r.v < 0.0f) {
            t->x = MAX(t->x, (max - r.p) / r.v);
            t->y = MIN(t->y, (min - r.p) / r.v);
            return 1;
        } else
            return 0;
    } else
        return ray1d_bound_inside(r, min, max, t);
}

int is_ray_in_bounds(ray3 ray, bounds3 bounds)
{
    vec2 t = {-FLT_INF, FLT_INF};

    for (size_t i = 0; i < 3; i++) {
        if (!ray1d_bound((ray1){((float*)&ray.p)[i], ((float*)&ray.v)[i]},
        ((float*)&bounds.min)[i], ((float*)&bounds.max)[i], &t))
            return 0;
    }
    return (t.x <= t.y);
}
