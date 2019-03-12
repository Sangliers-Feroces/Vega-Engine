/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

int poll_events(demo_t *demo)
{
    sfEvent event;

    if (!sfRenderWindow_isOpen(demo->win.window))
        return (0);
    while (sfRenderWindow_pollEvent(demo->win.window, &event))
        switch (event.type) {
            case sfEvtClosed:
            sfRenderWindow_close(demo->win.window);
            return (0);
            case sfEvtMouseButtonPressed:
            demo->mouse.mouse_pos = sfMouse_getPositionRenderWindow(demo->win.window);
            demo->mouse.first_click = 1;
            break;
            case sfEvtMouseButtonReleased:
            demo->mouse.first_click = 0;
            break;
            default:
            break;
        }
    check_mouse_move(demo);
    demo_poll_input(demo);
    return (1);
}

gluint get_texture(int w, int h, uint32_t pixel)
{
    gluint res;
    uint32_t *data = malloc(w * h * sizeof(uint32_t));

    for (size_t i = 0; i < (size_t)(w * h); i++)
        data[i] = pixel & i;
    glGenTextures(1, &res);

    glBindTexture(GL_TEXTURE_2D, res);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    free(data);

    return res;
}

void draw_quad(gluint buf, gluint program, vec2 pos, vec2 size, gluint texture)
{
    gluint pos_uni = glGetUniformLocation(program, "p");
    gluint size_uni = glGetUniformLocation(program, "s");

    glBindBuffer(GL_ARRAY_BUFFER, buf);
    glVertexAttribPointer(
    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
    2,                  // size
    GL_FLOAT,      	// type
    GL_FALSE,           // normalized?
    sizeof(float) * 2,// stride
    (void*)0            // array buffer offset
    );
    glUniform2fv(pos_uni, 1, (glfloat*)&pos);
    glUniform2fv(size_uni, 1, (glfloat*)&size);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 6); // Starting from vertex 0; 3 vertices total -> 1 triangle
}

void load_model(octree **tree);

int demo_loop(void)
{
    demo_t *demo = demo_init();
    vertex_struct_t v_struct;

    glEnable(GL_MULTISAMPLE);
    load_model(&demo->tree);
    printf("octree done !\n");
    struct timespec start, finish;
    double elapsed;
    clock_gettime(CLOCK_MONOTONIC, &start);
    demo->cam.aperture = octree_light_rtx(demo->tree, 1000000000 / 50);
    printf("%f\n", demo->cam.aperture);
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("%f seconds\n", elapsed);

    /*while (poll_events(demo)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        sfRenderWindow_display(demo->win.window);
    }*/
    v_struct = get_vertex_array_from_octree(demo);
	display_vertex_array(demo, v_struct);
	free(v_struct.v_array);
    demo_quit(demo);
    return (0);
}
