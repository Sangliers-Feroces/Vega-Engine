/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static model_editor_t get_grabber_hover(demo_t *demo)
{
    inter_ray3_ent inter;
    model_editor_t res = MODEL_EDITOR_MAX;
    float min_t = FLT_INF;

    for (size_t i = 0; i < 3; i++) {
        inter = entity_intersect(demo->editor.grabber_ent[i], demo->mouse.ray);
        if (inter.vertex == NULL)
            continue;
        if (inter.min_t < min_t) {
            res = MODEL_EDITOR_X + i;
            min_t = inter.min_t;
        }
    }
    return res;
}

void editor_grab(demo_t *demo)
{
    demo->editor.grabbed = get_grabber_hover(demo);
    demo->editor.grab_delta = (vec3){0.0f, 0.0f, 0.0f};
    demo->editor.grab_first = editor_grab_get_proj(demo);
    demo->editor.grab_now =  demo->editor.grab_first;
}

vec3 editor_grab_get_proj(demo_t *demo)
{
    inter_ray3_ent inter = {NULL, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, 0.0f};

    switch (demo->editor.grabbed) {
    case MODEL_EDITOR_X:
        vertex_intersect_ray_no_cull(demo->editor.grabber_ent[0]->vertex,
        demo->mouse.ray, &inter, 1);
        return (vec3){inter.p.x, 0.0f, 0.0f};
    case MODEL_EDITOR_Y:
        vertex_intersect_ray_no_cull(demo->editor.grabber_ent[1]->vertex,
        demo->mouse.ray, &inter, 1);
        return (vec3){0.0f, inter.p.y, 0.0f};
    case MODEL_EDITOR_Z:
        vertex_intersect_ray_no_cull(demo->editor.grabber_ent[2]->vertex,
        demo->mouse.ray, &inter, 1);
        return (vec3){0.0f, 0.0f, inter.p.z};
    default:
        return (vec3){0.0f, 0.0f, 0.0f};
    }
}

void editor_grab_update_delta(demo_t *demo)
{
    demo->editor.grab_now = editor_grab_get_proj(demo);
    demo->editor.grab_delta =
    vec3_sub(demo->editor.grab_now, demo->editor.grab_first);
}
