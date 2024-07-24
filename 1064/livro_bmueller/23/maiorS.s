.section .data
    I: .quad 0 # mapeado em %rax
    MAIOR: .quad 0 # mapeado em %rdi
    DATA_ITEMS: .quad 3, 67, 34, 222, 45, 75, 54, 34, 44, 33, 22, 11, 66, 0 # mapeado em %rbx
.section .text
.global _start
_start:
    movq $0, %rax
    movq DATA_ITEMS(, %rax, 8), %rdi
    movq $1, %rax

loop:
    movq DATA_ITEMS(, %rax, 8), %rbx
    cmpq $0, %rbx
    je fim_loop
    cmpq %rdi, %rbx
    jle fim_if
    movq %rbx, %rdi

fim_if:
    addq $1, %rax
    jmp loop

fim_loop:
    movq $60, %rax
    syscall

