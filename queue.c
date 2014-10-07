#include "queue.h"

/* initialize queue */
void Queue_init(Queue_T oQueue) {
    oQueue->head = 0;
    oQueue->tail = 0;
    oQueue->size = 0;
    oQueue->length = MAX_SIZE;
}

/* add item to queue */
void Queue_enqueue(Queue_T oQueue, void *item) {
    ASSERT(oQueue->size < oQueue->length);
    oQueue->arr[oQueue->tail] = item;
    oQueue->tail = (oQueue->tail + 1) % oQueue->length;
    oQueue->size++;
}

/* remove item from queue */
void *Queue_dequeue(Queue_T oQueue) {
    ASSERT(oQueue->size > 0);
    void *temp = oQueue->arr[oQueue->head];
    oQueue->head = (oQueue->head + 1) % oQueue->length;
    oQueue->size--;
    return temp;
}

/* check if queue is empty */
bool_t Queue_is_empty(Queue_T oQueue) {
    return oQueue->size == 0;
}
