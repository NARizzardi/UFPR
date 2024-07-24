.section .data
.section .text
.global _start
_start:
    movq $13, %rdi
    movq $60, %rax
    syscall
