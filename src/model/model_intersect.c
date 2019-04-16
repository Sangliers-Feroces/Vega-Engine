/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

// entity must be refreshed before being tested

dvec3 vertex_barycentric3(dvec3 p, vertex_t *vertex)
{
    (void)p;
    (void)vertex;
    /*dvec3 v0 = dvec3_sub(vertex[1].pos, vertex[0].pos);
    dvec3 v1 = dvec3_sub(vertex[2].pos, vertex[0].pos);
    dvec3 v2 = dvec3_sub(p, vertex[0].pos);
    float dot00 = dvec3_dot(v0, v0);
    float dot01 = dvec3_dot(v0, v1);
    float dot11 = dvec3_dot(v1, v1);
    float dot20 = dvec3_dot(v2, v0);
    float dot21 = dvec3_dot(v2, v1);
    float div = dot00 * dot11 - dot01 * dot01;
    dvec3 res;

    res.y = (dot11 * dot20 - dot01 * dot21) / div;
    res.z = (dot00 * dot21 - dot01 * dot20) / div;
    res.x = 1.0f - res.y - res.z;
    return res;*/
    return (dvec3){0.0, 0.0, 0.0};
}

static float intersect_plane(vertex_t *vertex, ray3 ray, float dotnv)
{
    (void)vertex;
    (void)ray;
    (void)dotnv;
    return 0.0;
    //return dvec3_dot(vertex[0].normal, dvec3_sub(vertex[0].pos, ray.p)) /
    //dotnv;
}

void vertex_intersect_ray_no_cull(vertex_t *vertex, ray3 ray,
inter_ray3_ent *inter, int authorize_oob)
{
    intersect_plane(NULL, ray, 0.0);
    (void)vertex;
    (void)ray;
    (void)inter;
    (void)authorize_oob;
    /*float dotnv = dvec3_dot(vertex[0].normal, ray.v);
    float t;
    dvec3 p;
    dvec3 bar;

    if (dotnv == 0.0f)
        return;
    t = intersect_plane(vertex, ray, dotnv);
    if (t < 0.0f)
        return;
    p = ray3_compute(ray, t);
    bar = vertex_barycentric3(p, vertex);
    if ((!authorize_oob) && (!is_barycentric_valid(bar)))
        return;
    inter->vertex = vertex;
    inter->p = p;
    inter->bar = bar;
    inter->min_t = t;*/
}

inter_ray3_ent entity_intersect(entity_t *entity, ray3 ray)
{
    size_t triangle_count = entity->model->vertex_count / 3;
    inter_ray3_ent inter = {NULL, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, 0.0f};

    for (size_t i = 0; i < triangle_count; i++)
        vertex_intersect_ray_no_cull(&entity->vertex[i * 3], ray, &inter, 0);
    return inter;
}
