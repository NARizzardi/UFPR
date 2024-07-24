.section .text
.globl _start
calcula_area:
    pushq %rbp
    movq %rsp, %rbp

    movq $3, %r9            # pi para r9
    movq  +16(%rbp), %rax   # move o parametro para rax
    imul %rax, %rax         # parametro ao quadrado
    imul %r9, %rax          # pi vezes parametro

    popq %rbp
    ret

_start:
    pushq %rbp
    movq %rsp, %rbp

    pushq $1                # int r = 3

    pushq -8(%rbp)          # chama funcao calcula_area
    call calcula_area
    addq $8, %rsp

    addq $8, %rsp           #retorno da funcao
    popq %rbp
    movq %rax, %rdi
    movq $60, %rax
    syscall
