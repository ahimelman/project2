/*
Queue ADT
*/

#ifndef QUEUE_H
#define QUEUE_H

#include "common.h"
#include "util.h"

#define MAX_SIZE 9

typedef struct Queue {
    void *arr[MAX_SIZE];
    uint32_t head;
    uint32_t tail;
    uint32_t size;
    uint32_t length;
} Queue;

typedef struct Queue *Queue_T;

void Queue_init(Queue_T oQueue);

void Queue_enqueue(Queue_T oQueue, void *item);

void *Queue_dequeue(Queue_T oQueue);

bool_t Queue_is_empty(Queue_T oQueue);

#endif                          /* QUEUE_H */
