/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** serialization for the GPU
*/

#ifndef _GPU_SERIAL_H
#define _GPU_SERIAL_H

void gpu_serial_write(gpu_serial_t *serial, int32_t data);
void gpu_serial_write_float(gpu_serial_t *serial, float data);
void gpu_serial_write_vec2(gpu_serial_t *serial, vec2 data);
void gpu_serial_write_vec3(gpu_serial_t *serial, vec3 data);

#endif
