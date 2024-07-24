.section .text
.global _start
_start:
    movq $0, %rax
    movq $10, %rbx
loop:
    cmpq %rbx, %rax
    jg fim_loop
    add $1, %rax
    jmp loop
fim_loop:
    movq %rax, %rdi
    movq $60, %rax
    syscall
