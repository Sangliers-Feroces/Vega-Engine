/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#ifndef _DEMO_STRUCT_H
#define _DEMO_STRUCT_H

typedef enum {
    ACTION_PAINT,
    ACTION_MOVE
} action_t;

typedef enum {
    KEY_DEL = 127
} keycode_t;

typedef struct {
    float size;
    int iter;
    float strenght;
} arg_t;

typedef struct {
    int key_last[256];
    int key_state[256];
    int key_press[256];
} input_t;

typedef struct {
    uint32_t w;
    uint32_t h;
    sfRenderWindow *window;
    float framelen;
    sfClock *frametime;
    int has_focus;
} win_t;

typedef struct {
    dvec3 pos;
    dvec3 rot;
    long double fovw;
    long double ratiowh;
    long double near;
    proj_type_t proj;
    mvp_t mvp;
    ray_viewport_t viewport;
} cam_t;

typedef struct {
    sfMouseButton button_last;
    sfMouseButton button_state;
    sfMouseButton button_release;
    sfMouseButton button_click;
    sfVector2i last_pos;
    sfVector2i mouse_pos;
    ray3 ray;
} mouse_t;

typedef struct {
    vertex_struct_t vertex_struct;
    gluint vertex_array_id;
    gluint world_vertex_array;
    gluint vertex_buffer;
    gluint lightmap_shader;
    gluint world_shader;
} buf_t;

typedef enum {
    GAME_EDITOR,
    GAME_PLAYING
} game_state_t;

typedef struct {
    game_state_t state;
    dvec3 pos;
    dvec3 speed;
    int is_grounded;
} player_t;

typedef struct {
    size_t count;
    size_t allocated;
    dvec3 *selection;
} vec_selection_t;

typedef struct {
    vec_selection_t selections;
    model_t *model[MODEL_EDITOR_MAX];
    gluint shader;
    glint mvp;
    dvec3 grab;
    dvec3 grab_first;
    dvec3 grab_now;
    dvec3 grab_delta;
    model_editor_t grabbed;
    entity_t *grabber_ent[3];
    int is_wireframe;
} editor_t;

typedef struct {
    sfVideoMode *resolution;
} setting_t;

typedef struct {
    action_t action;
    win_t win;
    cam_t cam;
    input_t input;
    world_t world;
    mouse_t mouse;
    player_t player;
    buf_t buf;
    texture_pannel_t texture_panel;
    editor_t editor;
    setting_t setting;
} demo_t;

#endif
