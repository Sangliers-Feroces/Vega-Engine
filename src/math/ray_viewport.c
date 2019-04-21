/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** rect
*/

#include "headers.h"

ray3 demo_get_ray(demo_t *demo)
{
    ray_viewport_t port = demo->cam.viewport;
    ivec2 pos = {demo->mouse.mouse_pos.x, demo->mouse.mouse_pos.y};
    long double ratiox;
    long double ratioy;

    ratiox = (long double)pos.x / (long double)(demo->win.w - 1);
    ratioy = (long double)pos.y / (long double)(demo->win.h - 1);
    return (ray3){demo->cam.pos, dvec3_normalize(
    dvec3_interpolate(dvec3_interpolate(port.tl, port.tr, ratiox),
    dvec3_interpolate(port.bl, port.br, ratiox), ratioy))};
}

void demo_refresh_viewport(demo_t *demo)
{
    ray_viewport_t fin;
    dvec3 res = {-demo->cam.ratiowh, 1.0f, 1.0f};
    dmat4 rot;

    fin.tl = res;
    fin.tr = (dvec3){-res.x, res.y, res.z};
    fin.bl = (dvec3){res.x, -res.y, res.z};
    fin.br = (dvec3){-res.x, -res.y, res.z};
    dmat4_rot_xy(demo->cam.rot, rot);
    for (size_t i = 0; i < 4; i++)
        (&fin.tl)[i] = dmat4_mul_dvec3(rot, (&fin.tl)[i]);
    demo->cam.viewport = fin;
}
