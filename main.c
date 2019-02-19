/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** main
*/

#include "headers.h"

int main(void)
{
    rtx_triangle triangle;
    octree *octree = octree_create(NULL);

    vec3 base = {(randf() - 0.5f) * 10000.0f, (randf() - 0.5f) * 10000.0f,
    (randf() - 0.5f) * 10000.0f};
    triangle = rtx_triangle_create((vec3[]){{base.x, base.y, base.z},
    {base.x + randf() * 10.0f, base.y + randf() * 10.0f,
    base.z + randf() * 10.0f}, {base.x + randf() * 10.0f,
    base.y + randf() * 10.0f, base.z + randf() * 10.0f}});
    for (size_t i = 0; i < 10000; i++) {
        octree_insert_triangle(&octree, &triangle);
        triangle.vertex[0].x += 2.0f;
        triangle.vertex[0].y -= 0.33f;
        triangle.vertex[0].z -= 10.0f;
        triangle.vertex[1].x += 2.1f;
        triangle.vertex[1].y -= 0.35f;
        triangle.vertex[1].z -= 12.0f;
        triangle.vertex[2].x += 1.9f;
        triangle.vertex[2].y -= 0.30f;
        triangle.vertex[2].z -= 0.0f;
    }
    octree_destroy(&octree);
    return (EXIT_SUCCESS);
}
