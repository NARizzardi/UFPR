.section .data
    HEADER: .quad 16                # 16 bytes de metadata
    TAM_BLOCO: .quad 4096
    topo_inicial_heap: .quad 0
    inicio_heap: .quad 0
    topo_heap: .quad 0

.section .text
.globl setup_brk
.globl dismiss_brk
.globl memory_alloc
.globl memory_free
.globl memory_mapping

setup_brk:
    pushq %rbp
    movq %rbp, %rsp

    movq $12, %rax                  # Altera brk, de acordo com o livro
    movq TAM_BLOCO, %rdi            # Retorna o valor de brk
    syscall
                                 
    movq %rax, topo_inicial_heap    # Define as variáveis globais inicialmente
    movq %rax, topo_heap
    movq %rax, inicio_heap

    popq %rbp
    ret


dismiss_brk: 
    pushq %rbp
    movq %rbp, %rsp

    movq $12, %rax                  # Altera brk
    movq topo_inicial_heap, %rdi    # Retorna o valor inicial de brk para zerar a heap
    syscall

    popq %rbp
    ret

memory_free: 
    pushq %rbp
    movq %rbp, %rsp
    
    movq %rdi, %r8                 # Move primeiro argumento presente em rdi
    subq HEADER, %r8
    movq $0, (%r8)                 # Marca o bloco como livre

    popq %rbp
    ret

memory_alloc: 
    pushq %rbp
    movq %rbp, %rsp

    popq %rbp
    ret

memory_mapping: 
    pushq %rbp
    movq %rbp, %rsp
    movq inicio_heap, %r14
    movq topo_heap, %r15

    initWhileImprime:
        cmpq %r15, %r14
        jge fimWhileImprime
        call imprimeHeader

        movq (%r14), %r12
        movq 8(%r14), %r13
        cmpq $1, %r12
        je imprimeOcupado

        movq %r13, %rdi
        call imprimeBlocoLivre
        jmp incrementaAtual

    imprimeOcupado:
        movq %r13, %rdi
        call imprimeBlocoOcupado

    incrementaAtual:
        addq 8(%r14), %r14
        addq HEADER, %r14
        jmp initWhileImprime
    
    fimWhileImprime:
        movq $10, %rdi
        call putchar
        movq $10, %rdi
        call putchar
        movq $10, %rdi
        call putchar
        movq $10, %rdi
        call putchar
        popq %rbp
        ret

imprimeHeader:
    pushq %rbp
    movq %rbp, %rsp
    movq $0, %r10

    initWhileHeader:
        cmpq HEADER, %r10
        jge fimWhileHeader
        movq $35, %rdi
        call putchar
        addq $1, %r10
        jmp initWhileHeader

    fimWhileHeader:
        popq %rbp
        ret



imprimeBlocoOcupado:
    pushq %rbp
    movq %rbp, %rsp
    movq %rdi, %rbx
    movq $0, %r10
    
    initWhileOcupado:
        cmpq %rbx, %r10
        jge fimWhileOcupado
        movq $43, %rdi
        call putchar
        addq $1, %r10
        jmp initWhileOcupado

    fimWhileOcupado:
        popq %rbp
        ret




imprimeBlocoLivre:
    pushq %rbp
    movq %rbp, %rsp
    movq %rdi, %rbx
    movq $0, %r10
    
    initWhileLivre:
        cmpq %rbx, %r10
        jge fimWhileOcupado
        movq $45, %rdi
        call putchar
        addq $1, %r10
        jmp initWhileLivre


    fimWhileLivre:
        popq %rbp
        ret
