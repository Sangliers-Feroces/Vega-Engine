/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#ifndef _DEMO_H
#define _DEMO_H

#define CAM_MOVE 15.0f
#define PLAYER_MOVE 20.0f
#define PLAYER_MAX_SPEED 10.0f

void demo_poll_input(demo_t *demo);
void check_mouse_move(demo_t *demo);

int demo(arg_t);
demo_t* demo_init(void);
void demo_quit(demo_t *demo);

void demo_render_geom(demo_t *demo);

arg_t get_data_from_arg(int ac, char **av);

void demo_loop(demo_t *demo);

int poll_events(demo_t *demo);

void init(void);
void quit(void);
void gl_gen(demo_t *demo);
void gl_delete(demo_t *demo);

void reset_matrix(demo_t *demo);
void refresh_vp(demo_t *demo, gluint program);
void send_aperture(demo_t *demo, gluint program);

void load_model(octree **tree);

void player_physics(demo_t *demo);

void demo_update_framerate(demo_t *demo);

demo_t *demo_get_texture_pannel(demo_t *demo);

void demo_texture_destroy(demo_t *demo);

ray3 demo_get_ray(demo_t *demo);
void demo_refresh_viewport(demo_t *demo);

int check_click_pos(sfVector2i mouse_pos, button_t button,
float width_screen, float height);

float get_random_float(float borne_min, float borne_max);
int get_random_int(int borne_min, int borne_max);
#endif
