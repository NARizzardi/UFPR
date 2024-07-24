.section .text
.globl _start
calcula_area:
    pushq %rbp
    movq %rsp, %rbp

    popq %rbp
    ret

_start:
    pushq %rbp
    movq %rsp, %rbp

    pushq $3
    pushq -8(%rbp)
    call calcula_area


    addq $8, %rsp
    popq %rbp
    


    movq $60, %rax
    syscall
