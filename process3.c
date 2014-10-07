#include "common.h"
#include "syslib.h"
#include "util.h"

/* shared variable across calls to _start*/
static uint64_t inst_count;

/* flag to distinguish first process from second */
static bool_t count_set = FALSE;

void _start(void)
{
    /* get time difference between calls */
    uint64_t diff = get_timer() - inst_count;
    
    if (!count_set) {
        /* on first call, get instruction count */
        count_set = TRUE;
        inst_count = get_timer();
        yield();
    } else {
        /* print results */
        print_str(0, 35, "yield instruction count: ");
        print_int(0, 60, (int) diff);
    }
    exit();
}
