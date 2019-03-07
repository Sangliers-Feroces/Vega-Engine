/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** main
*/

#include "headers.h"

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

/*static void add_random_triangle(octree **tree)
{
    rtx_triangle rtx = get_random_triangle();

    octree_insert_triangle(tree, &rtx);
}*/

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
    thread_init();
    srand(time(NULL));

    load_gl_fun();
    octree *tree = octree_create(NULL);
    load_model(&tree);
    gpu_serial_t serial = octree_serialize(tree);
    FILE *file = fopen("serial.txt", "wb+");
    fwrite(serial.data, 1, serial.size, file);
    fclose(file);
    printf("octree done !\n");
    struct timespec start, finish;
    double elapsed;
    clock_gettime(CLOCK_MONOTONIC, &start);
    octree_light_rtx(tree, 1000000000 / 1000);
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("%f seconds\n", elapsed);
    demo_loop(tree);
    octree_destroy(&tree);

    thread_quit();
    return (EXIT_SUCCESS);
}
