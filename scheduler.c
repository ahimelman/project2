/* scheduler.c */

#include "common.h"
#include "kernel.h"
#include "scheduler.h"
#include "util.h"

int scheduler_count;

/* Declare queues here */
Queue ready_q;
Queue blocked_q;

void scheduler(void)
{
    ++scheduler_count;
    pcb_t *next = (pcb_t *)Queue_dequeue(&ready_q);
    current_running = next;
    restore_context(next); 
}

void do_yield(void)
{
    // asm ("xchg %bx, %bx");
    Queue_enqueue(&ready_q, (void *)current_running);
    // asm ("xchg %bx, %bx");
    asm ("call scheduler_entry");
    // scheduler_entry();
    return;
}

void do_exit(void)
{
}

void block(void)
{
}

void unblock(void)
{
}

bool_t blocked_tasks(void)
{
}
