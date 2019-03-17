/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** main
*/

#include "headers.h"

rtx_triangle* get_random_triangle(void)
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
    rtx_triangle *rtx = rtx_triangle_create(triangle);

    octree_insert_triangle(tree, rtx);
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

int game(int argc, char **argv)
{
    (void)argc;
    (void)argv;
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
