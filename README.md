We first initialize the pcb for each task in kernel.c:_start(), and then add each to the ready queue.
We included our queue implementation in kernel.c because we needed to access NUM_TASKS, which is 
located in tasks.c. Instead of using an entry point variable in the PCB, we initialize the EIP variable to
the entry point associated with each task.

In scheduler entry, we store all registers excluding the callee save registers into the pcb struct. We don't need to save the callee save registers because when we restore context, we jump to the return address that was saved when scheduler_entry was called. This means we'll be returning to either do_yield() or do_exit(), which will restore these registers for us. We then store the previous base pointer as EBP and the previous stack pointer as ESP by accessing these values on the stack.

Whenever we call scheduler_entry, we invoke the call instruction by inlining the assembly in C. We found this was required because the compiler was for some reason inserting a leave instruction before the call to scheduler_entry, which would corrupt our stack. 
