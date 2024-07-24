.section .text
.globl _start

delta:
    pushq %rbp
    movq %rsp, %rbp
    pushq $0             # endereço para salvar o retorno
    pushq $1             # a na pilha
    pushq $1             # b na pilha
    pushq $1             # c na pilha

    movq -16(%rbp), %rax # a em registrador
    movq -24(%rbp), %rbx # b em registrador
    movq -32(%rbp), %rcx # c em registrador

    imul %rbx, %rbx      # b*b
    imul $4, %rax        # 4*a
    imul %rax, %rcx      # 4*a*c

    movq %rbx, -8(%rbp)  # move b*b para o endereco de retorno -8
    movq %rcx, -16(%rbp) # move 4*a*c para o endereco de retorno -16

    popq %rax
    popq %rax
    popq %rax
    popq %rdi
    popq %rbp
    ret


_start:
    call delta
    cmpq %rdi, %rax
    jg else

     if:
        movq $1, %rdi
        jmp fim_else

    else:
        movq $0, %rdi

    fim_else:
        movq $60, %rax
        syscall
