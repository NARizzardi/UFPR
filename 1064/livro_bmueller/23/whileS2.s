.section .text
.global _start
_start:
    movq $0, %rax
    movq $0, %rdi
while:
    cmp $12, %rax
    jge fim_while
    addq %rax, %rdi
    addq $1, %rax
    jmp while

fim_while:
    movq $60, %rax
    syscall
