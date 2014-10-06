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
    return;
}

void do_exit(void)
{
    asm ("call scheduler_entry");
    return;
}

void block(void)
{
    //print_str(0, 0, "blocking");
    //asm ("xchg %bx, %bx");
    Queue_enqueue(&blocked_q, (void *)current_running);
    asm ("call scheduler_entry");
    return;
}

void unblock(void)
{
    //print_str(0, 0, "un-blocking");
    //asm ("xchg %bx, %bx");
    Queue_enqueue(&ready_q, Queue_dequeue(&blocked_q));
}

bool_t blocked_tasks(void)
{
    return !Queue_is_empty(&blocked_q);
}
