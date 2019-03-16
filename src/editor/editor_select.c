/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static void select_point(demo_t *demo, vec3 p)
{
    for (size_t i = 0; i < demo->editor.selections.count; i++)
        if (vec3_eq(demo->editor.selections.selection[i], p)) {
            editor_remove_point(demo, p);
            return;
        }
    editor_select_point(demo, p);
}

static void select_point_triangle(demo_t *demo, inter_ray3 inter)
{
    vec3 nearest;
    float dist = FLT_INF;
    float dist_cur;

    for (size_t i = 0; i < 3; i++) {
        dist_cur = vec3_dist(inter.p, inter.triangle->vertex[i]);
        if (dist_cur < dist) {
            nearest = inter.triangle->vertex[i];
            dist = dist_cur;
        }
    }
    select_point(demo, nearest);
}

static void select_triangle(demo_t *demo, inter_ray3 inter)
{
    for (size_t i = 0; i < 3; i++)
        select_point(demo, inter.triangle->vertex[i]);
}

void editor_select(demo_t *demo, inter_ray3 inter)
{
    int is_shift = sfKeyboard_isKeyPressed(sfKeyLShift);

    if (!is_shift)
        demo->editor.selections.count = 0;
    if (inter.triangle == NULL)
        return;
    select_point_triangle(demo, inter);
}
