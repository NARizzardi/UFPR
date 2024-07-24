.section .data
    I: .quad 0
    A: .quad 0
.section .text
.global _start
_start:
    movq $0, A
    movq $0, I
    movq I, %rax

while:
    cmp $10, %rax
    jge fim_while
    movq A, %rdi
    addq %rax, %rdi
    movq %rdi, A
    addq $1, %rax
    movq %rax, I
    jmp while

fim_while:
    movq $60, %rax
    syscall
