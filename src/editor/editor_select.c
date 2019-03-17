/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static void select_point(demo_t *demo, vec3 p, int do_xor)
{
    int has_found = 0;

    for (size_t i = 0; i < demo->editor.selections.count; i++)
        if (vec3_eq(demo->editor.selections.selection[i], p))
            has_found = 1;
    if (has_found) {
        if (do_xor)
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
    select_point(demo, nearest, 1);
}

static void select_triangle(demo_t *demo, inter_ray3 inter)
{
    for (size_t i = 0; i < 3; i++)
        select_point(demo, inter.triangle->vertex[i], 0);
}

static void select_geom(demo_t *demo, inter_ray3 inter)
{
    int is_shift = sfKeyboard_isKeyPressed(sfKeyLShift);

    if (!is_shift)
        demo->editor.selections.count = 0;
    if (inter.triangle == NULL)
        return;
    if (sfKeyboard_isKeyPressed(sfKeyLControl))
        select_triangle(demo, inter);
    else
        select_point_triangle(demo, inter);
}

void editor_select(demo_t *demo, inter_ray3 inter)
{
    if (demo->mouse.button_release & (1 << sfMouseLeft)) {
        if (demo->editor.grabbed != MODEL_EDITOR_MAX) {
            demo->editor.grabbed = MODEL_EDITOR_MAX;
            demo->editor.grab =
            vec3_add(demo->editor.grab, demo->editor.grab_delta);
            demo->editor.grab_delta = (vec3){0.0f, 0.0f, 0.0f};
        } else {
            select_geom(demo, inter);
        }
    }
    if (demo->mouse.button_click & (1 << sfMouseLeft))
        editor_grab(demo);
    if (demo->mouse.button_state & (1 << sfMouseLeft)) {
        if (demo->editor.grabbed != MODEL_EDITOR_MAX)
            editor_grab_update_delta(demo);
    }
}
