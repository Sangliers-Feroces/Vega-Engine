/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static void merge_points(demo_t *demo)
{
    octree_add_triangle(&demo->tree, demo->editor.selections.selection);
}

static void create_geom(demo_t *demo)
{
    vec3 pos = vec3_adds(
    vec3_add(demo->cam.pos, spherical_to_cartesian_z(demo->cam.rot)), -0.5f);

    octree_add_triangle(&demo->tree,
    (vec3[]){{pos.x, pos.y, pos.z}, {pos.x, pos.y, pos.z + 1.0f},
    {pos.x + 1.0f, pos.y, pos.z}});
    octree_add_triangle(&demo->tree,
    (vec3[]){{pos.x + 1.0f, pos.y, pos.z}, {pos.x, pos.y, pos.z + 1.0f},
    {pos.x + 1.0f, pos.y, pos.z + 1.0f}});
}

static void editor_shortcut(demo_t *demo)
{
    if (demo->input.key_press['P'])
        _ui.display_ui = !_ui.display_ui;
    if (demo->input.key_press['T'] && (demo->editor.selections.count == 3))
        merge_points(demo);
    if (demo->input.key_press['F'])
        editor_flip(demo);
    if (demo->input.key_press[KEY_DEL])
        editor_del(demo);
    if (demo->input.key_press['E'])
        editor_extrude(demo);
    if (demo->input.key_press['C'])
        create_geom(demo);
    if (demo->input.key_press['W'])
        demo->editor.is_wireframe = !demo->editor.is_wireframe;
    if (demo->input.key_press['R'])
        editor_rot(demo);
    if (demo->input.key_press['U'])
        editor_uv(demo);
}

void editor(demo_t *demo)
{
    inter_ray3 inter;

    if (!demo->win.has_focus)
        return;
    editor_shortcut(demo);
    demo_refresh_viewport(demo);
    if (_ui.button_hovered != UIBUTTON_NONE)
        return;
    demo->mouse.ray = demo_get_ray(demo);
    inter = octree_intersect_ray(demo->tree, demo->mouse.ray);
    switch (demo->action) {
    case ACTION_MOVE:
        editor_select(demo, inter);
        break;
    case ACTION_PAINT:
        if (demo->mouse.button_state & (1 << sfMouseLeft))
            editor_paint(demo, inter);
        break;
    }
}
