/* tasks.c
 * This file specifies which threads and processes are run
 * You MUST NOT change this interface
 */

struct task_info {
    uint32_t entry_point;
    enum {
        KERNEL_THREAD,
        PROCESS,
    } task_type;
};

static struct task_info task1 = { (uint32_t) & clock_thread, KERNEL_THREAD };
static struct task_info task2 = { (uint32_t) & thread2, KERNEL_THREAD };
static struct task_info task3 = { (uint32_t) & thread3, KERNEL_THREAD };
static struct task_info task4 = { PROC1_ADDR, PROCESS }; /* PROC*_ADDR's are defined in Makefile */
static struct task_info task5 = { PROC2_ADDR, PROCESS };

static struct task_info time_switch_1 = { (uint32_t) & thread4, KERNEL_THREAD };
static struct task_info time_switch_2 = { (uint32_t) & thread5, KERNEL_THREAD };
static struct task_info time_switch_3 = { PROC3_ADDR, PROCESS };

static struct task_info *task[] = { &task1, &task2, &task3, &task4, &task5,
    &time_switch_1, &time_switch_2, &time_switch_3, &time_switch_3 }; //The duplication is intentional

enum {
    NUM_TASKS = sizeof task / sizeof(struct task_info *)
};
