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
    float limit = 100.0f;
    vec3 base = {(randf() - 0.5f) * limit, (randf() - 0.5f) * limit,
    (randf() - 0.5f) * limit};

    return rtx_triangle_create((vec3[]){{base.x, base.y, base.z},
    {base.x + randf() * 10.0f, base.y + randf() * 10.0f,
    base.z + randf() * 10.0f}, {base.x + randf() * 10.0f,
    base.y + randf() * 10.0f, base.z + randf() * 10.0f}});
}

static void add_triangle(octree **tree, vec3 *triangle)
{
    rtx_triangle rtx = rtx_triangle_create(triangle);

    octree_insert_triangle(tree, &rtx);
}

void load_model(octree **tree)
{
    //add_triangle(tree, (vec3[]){{0.0f, 0.0f, 0.0f},
    //{0.0f, 0.0f, 20.0f}, {20.0f, 0.0f, 0.0f}});
    add_triangle(tree, (vec3[]){{0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 20.0f}, {20.0f, 0.0f, 0.0f}});
    add_triangle(tree, (vec3[]){{0.0f, 1.0f, 0.0f},
    {10.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 10.0f}});
}

int main(void)
{
    //rtx_triangle triangle;

    srand(time(NULL));
    octree *tree = octree_create(NULL);
    /*for (size_t i = 0; i < 10000; i++) {
        triangle = get_random_triangle();
        octree_insert_triangle(&tree, &triangle);
    }*/
    load_model(&tree);
    printf("octree done !\n");
    clock_t start = clock();
    octree_light_rtx(tree, 50000000);
    printf("%f seconds\n", (float)(clock() - start) / (float)CLOCKS_PER_SEC);
    octree_destroy(&tree);
    /*octree *tree = octree_create(NULL);
    triangle = rtx_triangle_create((vec3[]){{0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}});
    octree_insert_triangle(&tree, &triangle);
    triangle = rtx_triangle_create((vec3[]){{0.0f, -50.0f, 0.0f},
    {1.0f, -45.0f, 0.0f}, {0.0f, -45.0f, 1.0f}});
    octree_insert_triangle(&tree, &triangle);
    triangle = rtx_triangle_create((vec3[]){{0.0f, 50.0f, 0.0f},
    {0.0f, 45.0f, 1.0f}, {1.0f, 45.0f, 0.0f}});
    octree_insert_triangle(&tree, &triangle);
    triangle = rtx_triangle_create((vec3[]){{50.0f, 50.0f, 50.0f},
    {55.0f, 50.0f, 50.0f}, {50.0f, 55.0f, 50.0f}});
    octree_insert_triangle(&tree, &triangle);
    for (size_t i = 0; i < 1000; i++) {
        triangle = get_random_triangle();
        octree_insert_triangle(&tree, &triangle);
    }
    clock_t start = clock();
    for (size_t i = 0; i < 37000; i++)
    octree_intersect_ray(octree, (ray3){{M_PI, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}});
    printf("%f seconds\n", (float)(clock() - start) / (float)CLOCKS_PER_SEC);*/
    return (EXIT_SUCCESS);
}
