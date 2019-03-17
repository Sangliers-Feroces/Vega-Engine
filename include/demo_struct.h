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
    KEY_UP = 0,
    KEY_DOWN = 1,
    KEY_LEFT = 2,
    KEY_RIGHT = 3,
    KEY_JUMP = 4,
    KEY_ATK = 5,
    KEY_UI = 6,
    KEY_COUNT = 7
} key_act_t;

typedef struct {
    sfKeyCode binding[KEY_COUNT];
    char keystate[KEY_COUNT];
} input_t;

typedef struct {
    uint32_t w;
    uint32_t h;
    sfRenderWindow *window;
    float framelen;
    sfClock *frametime;
} win_t;

typedef struct {
    vec3 pos;
    vec3 rot;
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
    gluint vertex_buffer;
    gluint lightmap_shader;
} buf_t;

typedef enum {
    GAME_EDITOR,
    GAME_PLAYING
} game_state_t;

typedef struct {
    game_state_t state;
    vec3 pos;
    vec3 speed;
    int is_grounded;
} player_t;

typedef struct {
    size_t count;
    size_t allocated;
    vec3 *selection;
} vec_selection_t;

typedef struct {
    vec_selection_t selections;
    model_t *model[MODEL_EDITOR_MAX];
    gluint shader;
    glint mvp;
    vec3 grab;
    vec3 grab_first;
    vec3 grab_now;
    vec3 grab_delta;
    model_editor_t grabbed;
    entity_t *grabber_ent[3];
} editor_t;

typedef struct {
    action_t action;
    win_t win;
    cam_t cam;
    input_t input;
    octree *tree;
    mouse_t mouse;
    player_t player;
    buf_t buf;
    texture_pannel_t texture_panel;
    editor_t editor;
} demo_t;

#endif
