#include "queue.h"

void Queue_init(Queue_T oQueue) {
    oQueue->head = 0;
    oQueue->tail = 0;
    oQueue->size = 0;
    oQueue->length = MAX_SIZE;
}

void Queue_enqueue(Queue_T oQueue, void *item) {
    static int counter = 0;
    counter++;
        print_int(3 + counter % 10, 0, oQueue->size);
        print_int(3 + counter % 10, 20, oQueue->length);
        print_int(3 + counter % 10, 40, counter);
    ASSERT(oQueue->size < oQueue->length);
    oQueue->arr[oQueue->tail] = item;
    oQueue->tail = (oQueue->tail + 1) % oQueue->length;
    oQueue->size++;
}

void *Queue_dequeue(Queue_T oQueue) {
    ASSERT(oQueue->size > 0);
    void *temp = oQueue->arr[oQueue->head];
    oQueue->head = (oQueue->head + 1) % oQueue->length;
    oQueue->size--;
    return temp;
}

bool_t Queue_is_empty(Queue_T oQueue) {
    return oQueue->size == 0;
}
