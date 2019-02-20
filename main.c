/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** main
*/

#include "headers.h"

#include <time.h>

rtx_triangle get_random_triangle(void)
{
    vec3 base = {(randf() - 0.5f) * 10000.0f, (randf() - 0.5f) * 10000.0f,
    (randf() - 0.5f) * 10000.0f};

    return rtx_triangle_create((vec3[]){{base.x, base.y, base.z},
    {base.x + randf() * 10.0f, base.y + randf() * 10.0f,
    base.z + randf() * 10.0f}, {base.x + randf() * 10.0f,
    base.y + randf() * 10.0f, base.z + randf() * 10.0f}});
}

int main(void)
{
    rtx_triangle triangle;

    /*for (size_t j = 1; j < 1000000; j *= 10) {
    octree *octree = octree_create(NULL);
    for (size_t i = 0; i < j; i++) {
        triangle = get_random_triangle();
        octree_insert_triangle(&octree, &triangle);
    }
    //printf("octree done !\n");
    clock_t start = clock();
    for (size_t i = 0; i < 10000; i++)
        octree_intersect_ray(octree, (ray3){{0.0, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}});
    //printf("%f seconds\n", (float)(clock() - start) / (float)CLOCKS_PER_SEC);
    printf("%zu %f\n", j, (float)(clock() - start) / (float)CLOCKS_PER_SEC);
    octree_destroy(&octree);
    }*/
    octree *octree = octree_create(NULL);
    triangle = rtx_triangle_create((vec3[]){{0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}});
    octree_insert_triangle(&octree, &triangle);
    triangle = rtx_triangle_create((vec3[]){{0.0f, -50.0f, 0.0f},
    {1.0f, -45.0f, 0.0f}, {0.0f, -45.0f, 1.0f}});
    octree_insert_triangle(&octree, &triangle);
    triangle = rtx_triangle_create((vec3[]){{0.0f, 50.0f, 0.0f},
    {0.0f, 45.0f, 1.0f}, {1.0f, 45.0f, 0.0f}});
    octree_insert_triangle(&octree, &triangle);
    octree_intersect_ray(octree, (ray3){{0.2, 1.0f, 0.2f}, {0.0f, -1.0f, 0.0f}});
    octree_destroy(&octree);
    return (EXIT_SUCCESS);
}
