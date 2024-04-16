.section .data
i: .quad 0
m: .quad 0
v: .quad 10, 30, 5, 10, 50

.section .text
.global _start
_start: 

movq v, %rdi
movq $60, %rax
syscall
