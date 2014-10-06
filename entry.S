# entry.S
##

	.data


	.text
	.code32

	.globl	kernel_entry
kernel_entry:
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
#        xchg %bx, %bx
        pushl %ebp
        movl %esp, %ebp
        cmpl $0, scheduler_count 
        je call_scheduler

# store all regs
        pushfl
        # put pointer to pcb_t in eax
        movl current_running, %eax
       
        # save basic regs
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
#        xchg %bx, %bx
        pushl %ebp
        movl %esp, %ebp
        
        movl ARG_PCB_PTR(%ebp), %eax
        pushl PCB_EFLAGS(%eax)
        popfl
        movl PCB_EBX(%eax), %ebx
        movl PCB_ESI(%eax), %esi
        movl PCB_EDI(%eax), %edi
        movl PCB_EBP(%eax), %ebp
        movl PCB_ESP(%eax), %esp
        movl PCB_EIP(%eax), %eax
        jmp %eax


