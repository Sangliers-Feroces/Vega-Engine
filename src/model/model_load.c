/*
** EPITECH PROJECT, 2019
** teck1
** File description:
** model_load
*/

#include "headers.h"

static model_obj_parsing_t model_obj_parsing_init(void)
{
    model_obj_parsing_t res;

    res.p = vec_vec3_init();
    res.n = vec_vec3_init();
    res.t = vec_vec2_init();
    res.f = vec_size3_init();
    return res;
}

static void model_obj_parsing_flush(model_obj_parsing_t *obj)
{
    obj->p.count = 0;
    obj->n.count = 0;
    obj->t.count = 0;
    obj->f.count = 0;
}

static void model_obj_parsing_destroy(model_obj_parsing_t *obj)
{
    vec_vec3_destroy(obj->p);
    vec_vec3_destroy(obj->n);
    vec_vec2_destroy(obj->t);
    vec_size3_destroy(obj->f);
}

static vec3 get_vec3(const char *line)
{
    vec3 res;

    sscanf(line, " %f %f %f", &res.x, &res.y, &res.z);
    return res;
}

static vec2 get_vec2(const char *line)
{
    vec2 res;

    sscanf(line, " %f %f", &res.x, &res.y);
    return res;
}

static void parse_v(const char *line, model_obj_parsing_t *obj)
{
    switch (line[1]) {
    case ' ':
        return vec_vec3_add(&obj->p, get_vec3(&line[2]));
    case 't':
        return vec_vec2_add(&obj->t, get_vec2(&line[2]));
    case 'n':
        return vec_vec3_add(&obj->n, get_vec3(&line[2]));
    }
}

static size_t get_next_space_pos(const char *str, size_t i)
{   
    size_t res = 0;

    for (; (str[i + res] != ' ') && (str[i + res] != '\0'); res++);
    return res;
}

static void go_to_token(const char *str, size_t *i, char token)
{
    for (; (str[*i] != token) && (str[*i] != '\0'); (*i)++);
}

static size3 extract_ndx(const char *line, size_t start)
{
    size3 res = {~0ULL, ~0ULL, ~0ULL};
    size_t i = start;

    go_to_token(line, &i, '/');
    if (line[i] == '\0')
        return res;
    if (line[i + 1] == '/')
        sscanf(&line[start], "%zu//%zu", &res.x, &res.z);
    else
        sscanf(&line[start], "%zu/%zu/%zu", &res.x, &res.y, &res.z);
    res.x--;
    res.y--;
    res.z--;
    return res;
}

static vertex_t vertex_from_obj(model_obj_parsing_t *obj, size3 ndx)
{
    vertex_t res;

    res.pos = (vec3){0.0, 0.0, 0.0};
    res.normal = (vec3){0.0, 0.0, 0.0};
    res.uv = (vec2){0.0, 0.0};
    if (ndx.x < obj->p.count)
        res.pos = obj->p.vec3[ndx.x];
    if (ndx.y < obj->t.count)
        res.uv = obj->t.vec2[ndx.y];
    if (ndx.z < obj->n.count)
        res.normal = obj->n.vec3[ndx.z];
    return res;
}

static void parse_f(const char *line, model_obj_parsing_t *obj,
mesh_full_t *res)
{
    size_t i = 1;
    size_t next;

    while (line[i] == ' ') {
        next = get_next_space_pos(line, i + 1);
        vec_size3_add(&obj->f, extract_ndx(line, i + 1));
        i += next + 1;
    }
    if (obj->f.count == 0)
        return;
    for (size_t i = 1; i < obj->f.count - 1; i++) {
        mesh_full_add_vertex(res, vertex_from_obj(obj, obj->f.size3[0]));
        mesh_full_add_vertex(res, vertex_from_obj(obj, obj->f.size3[i]));
        mesh_full_add_vertex(res, vertex_from_obj(obj, obj->f.size3[i + 1]));
    }
    vec_size3_flush(&obj->f);
}

mesh_full_t* mesh_load_obj(const char *filepath)
{
    FILE *file = fopen(filepath, "rb");
    mesh_full_t *res;
    size_t n = 0;
    char *line = NULL;
    model_obj_parsing_t obj = model_obj_parsing_init();
    size_t do_flush = 0;

    if (file == NULL)
        return NULL;
    res = mesh_full_create(1, 0);
    while (getline(&line, &n, file) >= 0) {
        if (line[0] == 'v') {
            if (do_flush) {
                model_obj_parsing_flush(&obj);
                do_flush = 0;
            }
            parse_v(line, &obj);
        }
        else if (line[0] == 'f') {
            parse_f(line, &obj, res);
            do_flush = 1;
        }
    }
    model_obj_parsing_destroy(&obj);
    fclose(file);
    free(line);
    return (res);
}
