/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** nvidia fanboyisme
*/

#ifndef _TEXTURE_H
#define _TEXTURE_H

texture2* texture2_create(uint32_t w, uint32_t h);
void texture2_destroy(texture2 *texture);
texture2_binding texture2_binding_create(vec3 *triangle);
void texture2_binding_destroy(texture2_binding binding);

void texture2_write(texture2 *texture);

texture2f* texture2f_create(uint32_t w, uint32_t h);
void texture2f_destroy(texture2f *texture);

void texture2f_reset(texture2f *texture);
float texture2f_get_max_lumel(texture2f *texture);
void texture_update_lightmap(texture2f *src, texture2 *dst, float max_lumel);
void texture2f_write_color_bar(texture2f *texture, vec2 *uv, vec3 bar,
vec3 color);

#endif
