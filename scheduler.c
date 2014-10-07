/* scheduler.c */

#include "common.h"
#include "kernel.h"
#include "scheduler.h"
#include "util.h"

int scheduler_count;

void scheduler(void)
{
    ++scheduler_count;

    /* Get next ready process, restore context */
    pcb_t *next = (pcb_t *)Queue_dequeue(ready_q);
    current_running = next;
    restore_context(next); 
}

void do_yield(void)
{
    Queue_enqueue(ready_q, (void *)current_running);
    asm ("call scheduler_entry");
    return;
}

void do_exit(void)
{
    asm ("call scheduler_entry");
    return;
}

void block(void)
{
    /* Add current process to blocked queue, context switch */
    Queue_enqueue(blocked_q, (void *)current_running);
    asm ("call scheduler_entry");
    return;
}

void unblock(void)
{
    /* Enqueue head of blocked queue into ready queue */
    Queue_enqueue(ready_q, Queue_dequeue(blocked_q));
}

bool_t blocked_tasks(void)
{
    return !Queue_is_empty(blocked_q);
}
