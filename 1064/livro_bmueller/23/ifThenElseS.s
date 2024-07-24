.section .data
    A: .quad 0
    B: .quad 0
.section .text
.global _start
_start:
    movq $4, B
    movq $5, A
    movq A, %rdi
    movq B, %rax
    cmp %rax, %rdi
    jl else

if:
    addq %rax, %rdi
    jmp fim_else

else:
    subq %rax, %rdi

fim_else:
    movq $60, %rax
    syscall

