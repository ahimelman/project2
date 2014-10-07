# entry.S
##

	.data


	.text
	.code32

.equ SYSCALL_ARG, 8

	.globl	kernel_entry
kernel_entry:
	pushl %ebp
	movl %esp, %ebp

# check which type of system call
	cmpl $0, SYSCALL_ARG(%ebp)
	je call_do_yield
	call do_exit
	jmp ret_kernel_entry
call_do_yield:
	call do_yield
ret_kernel_entry:	
	leave
	ret

.equ PCB_EAX, 4
.equ PCB_EBX, 8
.equ PCB_ECX, 12
.equ PCB_EDX, 16
.equ PCB_ESI, 20
.equ PCB_EDI, 24
.equ PCB_EBP, 28
.equ PCB_ESP, 32
.equ PCB_EIP, 36
.equ PCB_EFLAGS, 40

.equ STACK_EBP, 0
.equ STACK_EFLAGS, -4
.equ STACK_EIP, 4

	.globl	scheduler_entry
scheduler_entry:
        pushl %ebp
        movl %esp, %ebp

# don't save context first time        
        cmpl $0, scheduler_count 
        je call_scheduler

# store all regs
        pushfl
        # put pointer to pcb_t in eax
        movl current_running, %eax
       
        # save basic regs
        # don't save callee save b.c. they'll be restored by calling code
        movl %ebx, PCB_EBX(%eax)
        movl %esi, PCB_ESI(%eax)
        movl %edi, PCB_EDI(%eax)
       
        # store previous base pointer as EBP
        movl STACK_EBP(%ebp), %ebx
        movl %ebx, PCB_EBP(%eax)
        
        # store previous stack pointer as ESP
        movl %ebp, %ebx
        subl $8, %ebx
        movl %ebx, PCB_ESP(%eax)

        # store return address as EIP
        movl STACK_EIP(%ebp), %ebx
        movl %ebx, PCB_EIP(%eax)
        
        # store EFLAGS
        movl STACK_EFLAGS(%ebp), %ebx
        movl %ebx, PCB_EFLAGS(%eax)

call_scheduler:
        call scheduler

	leave
	ret
	
.equ ARG_PCB_PTR, 8

    .globl restore_context

restore_context:
        pushl %ebp
        movl %esp, %ebp
        
# move pointer to pcb into eax
        movl ARG_PCB_PTR(%ebp), %eax
        pushl PCB_EFLAGS(%eax)
        popfl
# restore regs
        movl PCB_EBX(%eax), %ebx
        movl PCB_ESI(%eax), %esi
        movl PCB_EDI(%eax), %edi
        movl PCB_EBP(%eax), %ebp
        movl PCB_ESP(%eax), %esp
        movl PCB_EIP(%eax), %eax
# jump to eip        
        jmp %eax


