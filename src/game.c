/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** main
*/

#include "headers.h"

static void add_triangle(octree **tree, vec3 *triangle)
{
    rtx_triangle *rtx = rtx_triangle_create(triangle);

    octree_insert_triangle(tree, rtx);
}

static void load_model_ext(octree **tree, float h)
{
    add_triangle(tree, (vec3[]){{0.0f, 3.0f - h, 0.0f},
    {10.0f, 3.0f - h, 0.0f}, {0.0f, 3.0f - h, 5.0f}});
    add_triangle(tree, (vec3[]){{0.0f, 3.0f - h, 5.0f},
    {10.0f, 3.0f - h, 0.0f}, {10.0f, 3.0f - h, 5.0f}});
    add_triangle(tree, (vec3[]){{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 5.0f},
    {10.0f, 0.0f, 0.0f}});
    add_triangle(tree, (vec3[]){{0.0f, 0.0f, 5.0f}, {10.0f, 0.0f, 5.0f},
    {10.0f, 0.0f, 0.0f}});
    add_triangle(tree, (vec3[]){{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 5.0f},
    {0.0f, 3.0f - h, 5.0f}});
    add_triangle(tree, (vec3[]){{0.0f, 3.0f - h, 5.0f}, {0.0f, 3.0f - h, 0.0f},
    {0.0f, 0.0f, 0.0f}});
    add_triangle(tree, (vec3[]){{0.0f, 0.0f, 0.0f},
    {0.0f, 3.0f - h, 5.0f}, {0.0f, 0.0f, 5.0f}});
    add_triangle(tree, (vec3[]){{0.0f, 3.0f - h, 5.0f},
    {0.0f, 0.0f, 0.0f}, {0.0f, 3.0f - h, 0.0f}});
    add_triangle(tree, (vec3[]){{10.0f, 0.0f, 0.0f}, {10.0f, 0.0f, 5.0f},
    {10.0f, 3.0f - h, 5.0f}});
    add_triangle(tree, (vec3[]){{10.0f, 3.0f - h, 5.0f},
    {10.0f, 3.0f - h, 0.0f}, {10.0f, 0.0f, 0.0f}});
}

void load_model(octree **tree)
{
    float h = 0.0f;

    add_triangle(tree, (vec3[]){{0.0f, 0.0f, 5.0f},
    {0.0f, 3.0f - h, 5.0f}, {10.0f, 0.0f, 5.0f}});
    add_triangle(tree, (vec3[]){{0.0f, 3.0f - h, 5.0f}, {10.0f, 3.0f - h, 5.0f},
    {10.0f, 0.0f, 5.0f}});
    add_triangle(tree, (vec3[]){{0.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f}, {10.0f, 0.0f, 0.0f}});
    add_triangle(tree, (vec3[]){{0.0f, 1.0f, 0.0f}, {10.0f, 1.0f, 0.0f},
    {10.0f, 0.0f, 0.0f}});
    add_triangle(tree, (vec3[]){{0.0f, 2.0f, 0.0f},
    {0.0f, 3.0f - h, 0.0f}, {10.0f, 2.0f, 0.0f}});
    add_triangle(tree, (vec3[]){{0.0f, 3.0f - h, 0.0f}, {10.0f, 3.0f - h, 0.0f},
    {10.0f, 2.0f, 0.0f}});
    add_triangle(tree, (vec3[]){{0.0f, 3.0f - h, 0.0f}, {0.0f, 3.0f - h, 5.0f},
    {10.0f, 3.0f - h, 0.0f}});
    add_triangle(tree, (vec3[]){{0.0f, 3.0f - h, 5.0f}, {10.0f, 3.0f - h, 5.0f},
    {10.0f, 3.0f - h, 0.0f}});
    load_model_ext(tree, h);
}

int game(int argc, char **argv)
{
    if (argc > 1)
        if (strcmp(argv[1], "-h") == 0) {
            display_helper();
            return 0;
        }
    demo();
    return (EXIT_SUCCESS);
}

void display_helper(void)
{
    int len;
    int fd;
    char buff[2048];

    fd = open("readme.md", O_RDONLY);
    len = read(fd, buff, 2048);
    buff[len] = '\0';
    my_putstr(buff);
}
