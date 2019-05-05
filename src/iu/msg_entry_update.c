/*
** EPITECH PROJECT, 2019
** MUL_my_world_2018
** File description:
** iu_draw
*/

#include "headers.h"

static void vec_msg_update(vec_msg_entry_t *vec)
{
    for (size_t i = 0; i < vec->count; i++)
        if (vec->msg[i].life < _demo->clocks.t) {
            vec_msg_entry_delete(vec, i);
            i--;
        }
}

void vec_msg_display(vec_msg_entry_t *vec)
{
    vec_msg_update(vec);

}

void msg_add(char *msg, double duration)
{
    vec_msg_entry_add(&_demo->buf.msgs,
    msg_entry_create(msg, _demo->clocks.t + duration));
}
