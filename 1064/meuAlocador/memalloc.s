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

    # encontrar o bloco seguindo a diretiva
    call worst_fit
    # call best_fit
    # call first_fit

    # se nao existe bloco aumenta a brk
    # se existe avalia tamanho do bloco
    # se bloco for ate 9 bytes a mais só altera o estado e retorna o endereco
    # se tamanho do bloco tiver 10 ou mais bytes livres, reparticiona

    popq %rbp
    ret

