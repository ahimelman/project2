#include "common.h"
#include "scheduler.h"
#include "util.h"

/* shared variable across threads */
static uint64_t num_inst;

void thread4(void)
{
    /* get timer, yield to thread5 */
    num_inst = get_timer();
    do_yield();
    do_exit();
}

void thread5(void)
{
    /* get difference, print result */
    uint64_t diff = get_timer() - num_inst;
    print_str(0, 0, "do_yield instruction count: ");
    print_int(0, 28, (int) diff);
    do_exit();
}
