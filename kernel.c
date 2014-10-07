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
   
    Queue_init(&ready_q);
    Queue_init(&blocked_q);
   
    /* Initialize pcb for each task */ 
    for (i = 0; i < NUM_TASKS; i++) {
        pcbs[i].pid = i;
        stack_start = STACK_MIN + (STACK_SIZE * (1 + (i * 2)));
        pcbs[i].esp = stack_start + STACK_SIZE - 2;
        pcbs[i].ebp = stack_start + STACK_SIZE - 2;
        pcbs[i].is_thread = (task[i]->task_type == KERNEL_THREAD);
        pcbs[i].eip = task[i]->entry_point;

        /* Add pcb to ready queue */
        Queue_enqueue(&ready_q, (void *)&pcbs[i]);
    }

    /* Schedule the first task */
    scheduler_count = 0;
    scheduler_entry();

    /* We shouldn't ever get here */
    ASSERT(0);
}

