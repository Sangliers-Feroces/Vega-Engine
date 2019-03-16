/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** headers
*/

#ifndef _THREAD_STRUCT_H
#define _THREAD_STRUCT_H

#define THREAD_DATA_SIZE 128

typedef enum {
    THREAD_TASK_IDLE,
    THREAD_TASK_ABORT,
    THREAD_TASK_KILL,
    THREAD_TASK_RAY_TRACING
} thread_task;

typedef struct {
    pthread_t id;
    thread_task task;
    uint64_t data[THREAD_DATA_SIZE];
    int is_busy;
    float progress;
} thread_bus;

typedef struct {
    size_t count;
    thread_bus *bus;
} threads;

#endif
