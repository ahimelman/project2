# entry.S
##

	.data


	.text
	.code32

	.globl	kernel_entry
kernel_entry:
	ret

.equ PCB_EAX 4
.equ PCB_EBX 8 
.equ PCB_ECX 12
.equ PCB_EDX 16
.equ PCB_ESI 20
.equ PCB_EDI 24
.equ PCB_EBP 28
.equ PCB_ESP 32
.equ PCB_EIP 36
.equ PCB_EFLAGS 40

.equ STACK_EBP 0
.equ STACK_EFLAGS -4
.equ STACK_EAX -8
.equ STACK_EIP 4

	.globl	scheduler_entry

scheduler_entry:
        pushl %ebp
        movl %esp, %ebp
        cmpl scheduler_count, $0 
        je call_scheduler

# store all regs
        pushfl
        pushl %eax
        movl current_running, %eax
        movl %ebx, PCB_EBX(%eax)
        movl %ecx, PCB_ECX(%eax)
        movl %edx, PCB_EDX(%eax)
        movl %esi, PCB_ESI(%eax)
        movl %edi, PCB_EDI(%eax)
        movl STACK_EBP(%ebp), %ebx
        movl %ebx, PCB_EBP(%eax)
        movl %ebp, %ebx
        subl $8, %ebx
        movl %ebx, PCB_ESP(%eax)
        movl STACK_EIP(%ebp), %ebx
        movl %ebx, PCB_EIP(%eax)
        movl STACK_EFLAGS(%ebp), %ebx
        movl %ebx, PCB_EFLAGS(%eax)
        movl STACK_EAX(%ebp), %ebx
        movl %ebx, PCB_EAX(%eax)

call_scheduler:   
	call scheduler
