/* kernel.c */

#include "common.h"
#include "kernel.h"
#include "scheduler.h"
#include "th.h"
#include "util.h"

#include "tasks.c"

pcb_t *current_running;

/* This function is the entry point for the kernel
 * It must be the first function in the file
 */
void _start(void)
{
    int i;
    uint32_t stack_start;
    /* Set up the single entry-point for system calls */
    *ENTRY_POINT = &kernel_entry;

    clear_screen(0, 0, 80, 25);

    /* Initialize the pcbs and the ready queue */
    static pcb_t pcbs[NUM_TASKS];
   
    Queue_init(ready_q);
    Queue_init(blocked_q);
   
    /* Initialize pcb for each task */ 
    for (i = 0; i < NUM_TASKS; i++) {
        pcbs[i].pid = i;
        stack_start = STACK_MIN + (STACK_SIZE * (1 + (i * 2)));
        pcbs[i].esp = stack_start + STACK_SIZE - 2;
        pcbs[i].ebp = stack_start + STACK_SIZE - 2;
        pcbs[i].is_thread = (task[i]->task_type == KERNEL_THREAD);
        pcbs[i].eip = task[i]->entry_point;

        /* Add pcb to ready queue */
        Queue_enqueue(ready_q, (void *)&pcbs[i]);
    }

    /* Schedule the first task */
    scheduler_count = 0;
    scheduler_entry();

    /* We shouldn't ever get here */
    ASSERT(0);
}


/* Queue code included here because we need NUM_TASKS*/
typedef struct Queue {
    void *arr[NUM_TASKS];
    uint32_t head;
    uint32_t tail;              
    uint32_t size;
    uint32_t length;
} Queue;

/* Declare queues here */
Queue ready_q_struct;
Queue blocked_q_struct;
Queue_T ready_q = &ready_q_struct;
Queue_T blocked_q = &blocked_q_struct;

/* initialize queue */
void Queue_init(Queue_T oQueue) {
    oQueue->head = 0;
    oQueue->tail = 0;
    oQueue->size = 0;
    oQueue->length = NUM_TASKS;
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

