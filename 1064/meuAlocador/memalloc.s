.section .data
    HEADER: .quad 16                # 16 bytes de metadata
    topo_inicial_heap: .quad 0
    inicio_heap: .quad 0
    topo_heap: .quad 0

.section .text
.global setup_brk
.global dismiss_brk
.global memory_alloc
.global memory_free
.global memory_mapping

setup_brk:
    pushq %rbp
    movq %rbp, %rsp

    movq $12, %rax                  # Altera brk, de acordo com o livro
    movq $0, %rdi                   # Retorna o valor de brk
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
    
    movq %rdi, rbx
    subq HEADER, %rbx
    movq $0, (%rbx)                 # Marca o bloco como livre

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

    popq %rbp
    ret
