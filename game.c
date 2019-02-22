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
    /*add_triangle(tree, (vec3[]){{0.0f, 3.5f, 0.0f},
    {1.0f, 3.5f, 20.0f}, {10.0f, 3.5f, 0.0f}});
    add_triangle(tree, (vec3[]){{0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 20.0f}, {20.0f, 0.0f, 0.0f}});
    add_triangle(tree, (vec3[]){{0.0f, 3.0f, 0.0f},
    {10.0f, 3.0f, 0.0f}, {0.0f, 3.0f, 10.0f}});*/

    add_triangle(tree, (vec3[]){{0.0f, 0.0f, 5.0f},
    {0.0f, 3.0f, 5.0f}, {10.0f, 0.0f, 5.0f}});
    add_triangle(tree, (vec3[]){{0.0f, 3.0f, 5.0f}, {10.0f, 3.0f, 5.0f},
    {10.0f, 0.0f, 5.0f}});

    add_triangle(tree, (vec3[]){{0.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f}, {10.0f, 0.0f, 0.0f}});
    add_triangle(tree, (vec3[]){{0.0f, 1.0f, 0.0f}, {10.0f, 1.0f, 0.0f},
    {10.0f, 0.0f, 0.0f}});
    add_triangle(tree, (vec3[]){{0.0f, 2.0f, 0.0f},
    {0.0f, 3.0f, 0.0f}, {10.0f, 2.0f, 0.0f}});
    add_triangle(tree, (vec3[]){{0.0f, 3.0f, 0.0f}, {10.0f, 3.0f, 0.0f},
    {10.0f, 2.0f, 0.0f}});

    add_triangle(tree, (vec3[]){{0.0f, 3.0f, 0.0f}, {0.0f, 3.0f, 5.0f},
    {10.0f, 3.0f, 0.0f}});  //ceil
    add_triangle(tree, (vec3[]){{0.0f, 3.0f, 5.0f}, {10.0f, 3.0f, 5.0f},
    {10.0f, 3.0f, 0.0f}});
    add_triangle(tree, (vec3[]){{0.0f, 3.0f, 0.0f},
    {10.0f, 3.0f, 0.0f}, {0.0f, 3.0f, 5.0f}});
    add_triangle(tree, (vec3[]){{0.0f, 3.0f, 5.0f},
    {10.0f, 3.0f, 0.0f}, {10.0f, 3.0f, 5.0f}});


    add_triangle(tree, (vec3[]){{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 5.0f},
    {10.0f, 0.0f, 0.0f}});
    add_triangle(tree, (vec3[]){{0.0f, 0.0f, 5.0f}, {10.0f, 0.0f, 5.0f},
    {10.0f, 0.0f, 0.0f}});

    add_triangle(tree, (vec3[]){{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 5.0f},
    {0.0f, 3.0f, 5.0f}}); //left
    add_triangle(tree, (vec3[]){{0.0f, 3.0f, 5.0f}, {0.0f, 3.0f, 0.0f},
    {0.0f, 0.0f, 0.0f}});
    add_triangle(tree, (vec3[]){{0.0f, 0.0f, 0.0f},
    {0.0f, 3.0f, 5.0f}, {0.0f, 0.0f, 5.0f}});
    add_triangle(tree, (vec3[]){{0.0f, 3.0f, 5.0f},
    {0.0f, 0.0f, 0.0f}, {0.0f, 3.0f, 0.0f}});
    add_triangle(tree, (vec3[]){{10.0f, 0.0f, 0.0f}, {10.0f, 0.0f, 5.0f},
    {10.0f, 3.0f, 5.0f}}); //right
    add_triangle(tree, (vec3[]){{10.0f, 3.0f, 5.0f}, {10.0f, 3.0f, 0.0f},
    {10.0f, 0.0f, 0.0f}});
}

int game(void)
{
    octree *tree = octree_create(NULL);
    load_model(&tree);
    printf("octree done !\n");
    clock_t start = clock();
    octree_light_rtx(tree, 1000000000 / 100);
    printf("%f seconds\n", (float)(clock() - start) / (float)CLOCKS_PER_SEC);
    demo_loop(tree);
    octree_destroy(&tree);
    return (EXIT_SUCCESS);
}
