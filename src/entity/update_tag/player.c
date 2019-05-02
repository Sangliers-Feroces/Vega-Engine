/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static void slow_ent_down(entity3 *ent)
{
    dvec3 d = dvec3_normalize(dvec3_init(
    ent->trans.speed.x, 0.0, ent->trans.speed.z));
    dvec3 f = dvec3_muls(d, _demo->win.framelen * 8.0);
    double norm = dvec3_norm(ent->trans.speed);

    if (norm > 1.0)
        ent->trans.speed = dvec3_sub(ent->trans.speed, f);
    else
        ent->trans.speed = dvec3_sub(ent->trans.speed, dvec3_muls(
        ent->trans.speed, _demo->win.framelen * 6.0));
}

static void cap_ent_speed(dvec3 *speed)
{
    vec2 xz = {speed->x, speed->z};
    float dist = vec2_norm(xz);
    double max = sfKeyboard_isKeyPressed(sfKeyLShift) ?
    PLAYER_MAX_SPEED : PLAYER_MAX_SPEED_WALK;

    if (dist > max) {
        xz = vec2_muls(xz, max / dist);
        *speed = (dvec3){xz.x, speed->y, xz.y};
    }
}

static void anim(entity3 *ent)
{
    entity3_tag_player_data_t *data = ent->tag_data;
    double d = dvec3_norm(ent->trans.speed);
    entity3 *to_m = ent->sub.ent[0]->sub.ent[0]->sub.ent[0];

    switch (data->state) {
    case PLAYER_REG:
        to_m->trans.rot = dvec3_init(0.0, 0.0, 0.0);
        data->anim_state += _demo->win.framelen * CLAMP(d, 1.0, 15.0);
        to_m->trans.pos.x = sin(data->anim_state / 3.14) / 10.0;
        to_m->trans.pos.y = cos(data->anim_state) / 30.0;
        to_m->trans.pos.z = 0.0;
        break;
    case PLAYER_ATK:
        data->anim_state += _demo->win.framelen * 4.0;
        d = sin(data->anim_state * M_PI);
        if (d > 0.5)
            data->has_atk += data->has_atk < 2;
        to_m->trans.rot.x = -d * 6.0 * 0.2;
        to_m->trans.rot.y = -d * 0.2;
        to_m->trans.pos.y = d * 0.2;
        to_m->trans.pos.z = d * 0.2;
        break;
    case PLAYER_BOOM:
        data->has_atk = 1;
        data->anim_state += _demo->win.framelen * 1.0;
        to_m->trans.rot.x = -data->anim_state * 8.0;
        to_m->trans.rot.y = data->anim_state * 4.0 * 8.0;
        to_m->trans.pos.y = data->anim_state * 8.0;
        to_m->trans.pos.z = data->anim_state * 8.0;
        break;
    default:
        break;
    }
}

static void state(entity3 *ent)
{
    entity3_tag_player_data_t *data = ent->tag_data;

    if (_demo->mouse.button_click & (1 << sfMouseLeft)) {
        data->state = PLAYER_ATK;
        data->anim_state = 0.0;
        data->has_atk = 0;
    }
    if (_demo->mouse.button_click & (1 << sfMouseRight)) {
        data->state = PLAYER_BOOM;
        data->anim_state = 0.0;
        data->has_atk = 0;
    }
    switch (data->state) {
    case PLAYER_BOOM:
    case PLAYER_ATK:
        if (data->anim_state > 1.0) {
            data->state = PLAYER_REG;
            data->anim_state = 0.0;
            data->has_atk = 0;
        }
        break;
    default:
        break;
    }
}

void entity3_tag_update_player(entity3 *ent)
{
    dvec3 cam_x;
    dvec3 cam_z;
    entity3 *ref_move = ent->trans.is_physics ? ent : ent->sub.ent[0];

    entity3_tag_update_player_poll_mouse(ent);
    cam_x = dvec3_muls(dmat4_mul_dvec3(ref_move->trans.world_rot,
    dvec3_init(1.0, 0.0, 0.0)), _demo->win.framelen);
    cam_z = dvec3_muls(dmat4_mul_dvec3(ref_move->trans.world_rot,
    dvec3_init(0.0, 0.0, 1.0)), _demo->win.framelen);
    if (ent->trans.is_physics)
        entity3_tag_update_player_poll_playing(ent, cam_x, cam_z);
    else
        entity3_tag_update_player_poll_editor(ent, cam_x, cam_z);
    if (ent->trans.is_grounded)
        slow_ent_down(ent);
    cap_ent_speed(&ent->trans.speed);
    state(ent);
    anim(ent);
}

void entity3_tag_init_player(void *pdata)
{
    entity3_tag_player_data_t *data = pdata;

    data->state = PLAYER_REG;
    data->anim_state = 0.0;
}
