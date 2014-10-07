#include "common.h"
#include "syslib.h"
#include "util.h"

static uint64_t inst_count;
static bool_t count_set = FALSE;

void _start(void)
{
    uint64_t diff = get_timer() - inst_count;
    if (!count_set) {
        count_set = TRUE;
        inst_count = get_timer();
        yield();
    } else {
        print_str(0, 35, "yield instruction count: ");
        print_int(0, 60, (int) diff);
    }
    exit();
}
