/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** rect
*/

#include "headers.h"

ray3 demo_get_ray(demo_t *demo, ivec2 pos)
{
    ray_viewport_t port = demo->cam.viewport;
    long double ratiox;
    long double ratioy;

    ratiox = (long double)pos.x / (long double)(demo->win.w - 1);
    ratioy = (long double)pos.y / (long double)(demo->win.h - 1);
    return (ray3){demo->cam.pos, vec3_normalize(
    vec3_interpolate(vec3_interpolate(port.tl, port.tr, ratiox),
    vec3_interpolate(port.bl, port.br, ratiox), ratioy))};
}

void demo_refresh_viewport(demo_t *demo)
{
    ray_viewport_t fin;
    vec3 res = {M_PI / 4.0f,
    M_PI / 4.0f * 1.15f, 0.0f};

    fin.tl = res;
    fin.tr = (vec3){res.x, -res.y, res.z};
    fin.bl = (vec3){-res.x, res.y, res.z};
    fin.br = (vec3){-res.x, -res.y, res.z};
    for (size_t i = 0; i < 4; i++)
        (&fin.tl)[i] = spherical_to_cartesian_z(vec3_add((&fin.tl)[i],
        demo->cam.rot));
    demo->cam.viewport = fin;
}
