/* lock.c: mutual exclusion
 * If SPIN is false, lock_acquire() should block the calling process until its request can be satisfied
 * Your solution must satisfy the FIFO fairness property
 */

#include "common.h"
#include "lock.h"
#include "scheduler.h"

enum {
    SPIN = FALSE,
};

void lock_init(lock_t * l)
{
    if (SPIN) {
        l->status = UNLOCKED;
    } else {
        l->status = UNLOCKED;
    }
}

void lock_acquire(lock_t * l)
{
    if (SPIN) {
        while (LOCKED == l->status)
            do_yield();
        l->status = LOCKED;
    } else {
        if (l->status == UNLOCKED) {
            l->status = LOCKED;
        } else {
            block();
        }
    }
}

void lock_release(lock_t * l)
{
    if (SPIN) {
        l->status = UNLOCKED;
    } else {
        if (blocked_tasks()) {
            unblock();
        } else {
            l->status = UNLOCKED;
        }
    }
}
