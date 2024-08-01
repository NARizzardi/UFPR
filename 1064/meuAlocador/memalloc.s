.section .data
    HEADER: .quad 16                # 16 bytes de metadata, 8 para uso + 8 para tamanho
    TAM_BLOCO: .quad 1024
    .globl topo_inicial_heap
    topo_inicial_heap: .quad 0

.section .text
.globl setup_brk, dismiss_brk, memory_alloc, memory_free, memory_mapping


# --------------------------------------------------------
# Nao ha utilizacao de registradores nesse procedimento
# --------------------------------------------------------
get_brk:                            # Funcao muito recorrente, melhor modularizada
    pushq %rbp
    movq %rsp, %rbp

    movq $12, %rax
    movq $0, %rdi                   # Retorna o valor atual de brk
    syscall

    popq %rbp
    ret


# --------------------------------------------------------
# %r15 - Parametro (tamanho a ser alocado)
# --------------------------------------------------------
refresh_brk:
    pushq %rbp
    movq %rsp, %rbp

    movq $12, %rax
    movq %r15, %rdi                   # Aumenta o valor atual de brk
    syscall

    popq %rbp
    ret

# --------------------------------------------------------
# %rax - Retorno de get_brk (valor inicial de brk)
# --------------------------------------------------------
setup_brk:
    pushq %rbp
    movq %rsp, %rbp

    call get_brk                    # Pega o valor inicial de brk

    movq %rax, topo_inicial_heap    # Define a origem da Heap
    
    popq %rbp
    ret

# --------------------------------------------------------
# Nao ha utilizacao de registradores nesse procedimento
# --------------------------------------------------------
dismiss_brk: 
    pushq %rbp
    movq %rsp, %rbp

    movq $12, %rax                  # Altera brk
    movq topo_inicial_heap, %rdi    # Retorna o valor inicial de brk para zerar a heap
    syscall

    popq %rbp
    ret


# --------------------------------------------------------
# 
# --------------------------------------------------------
memory_free: 
    pushq %rbp
    movq %rsp, %rbp
    
    movq %rdi, %r15                 # Move o parâmetro (enredeco a ser liberado) para %r15

    subq HEADER, %r15               # Verificar se o endereco passado é do inicio da area de memoria ou da header (se for header nao precisa desse subq)
    movq $0, (%r15)                 # Marca o bloco como livre

    movq $1, %rax
    popq %rbp
    ret


# --------------------------------------------------------
# %r15 - Parâmetro (tamano a ser alocado)
# %r14 - Maior valor encontrado (utilizado pelo worst-fit)
# %r12 - Endereco do bloco a ser utilizado 
# %r10 - Registradores com valores usados em comparacoes
# %rbx - Endereco do brk para percorrer a heap
# --------------------------------------------------------

memory_alloc: 
    pushq %rbp
    movq %rsp, %rbp

    movq %rdi, %r15                 # Move o parametro (tamanho a ser alocado) para %r15
    movq topo_inicial_heap, %rbx

    call get_brk
    cmpq %rbx, %rax                 # Verifica se a heap esta vazia
    je empty_heap

    # encontrar o bloco seguindo a diretiva
    worst_fit:


    cmpq $0, %r10
    jne reuse_block

    # se nao existe bloco aumenta a brk
    expand_heap:
    
    
    # se existe avalia tamanho do bloco
    reuse_block:
    
    # se bloco for ate 9 bytes a mais só altera o estado e retorna o endereco
    cmpq $10, %r12
    jl end_allocation
    # se tamanho do bloco tiver 10 ou mais bytes livres, reparticiona
    repartition:
    jmp end_allocation

    empty_heap:
        movq $1, (%r12)
        addq $8, %r12
        movq %r15, (%r12)


    end_allocation:
    movq %r12, %rdi
    popq %rbp
    ret

