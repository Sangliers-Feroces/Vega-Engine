/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** serialization for the GPU
*/

#include "headers.h"

void gpu_serial_write(gpu_serial_t *serial, int32_t data)
{
    serial->data[serial->size++] = data;
}

void gpu_serial_write_float(gpu_serial_t *serial, float data)
{
    gpu_serial_write(serial, FLOAT_BITS_TO_INT(data));
}

void gpu_serial_write_vec2(gpu_serial_t *serial, vec2 data)
{
    gpu_serial_write_float(serial, data.x);
    gpu_serial_write_float(serial, data.y);
}

void gpu_serial_write_vec3(gpu_serial_t *serial, vec3 data)
{
    gpu_serial_write_float(serial, data.x);
    gpu_serial_write_float(serial, data.y);
    gpu_serial_write_float(serial, data.z);
}
