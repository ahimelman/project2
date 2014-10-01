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
}

void do_yield(void)
{
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
