.section .data
    HEADER: .quad 16                 # 16 bytes de metadata, 8 para uso + 8 para tamanho
    .globl topo_inicial_heap
    topo_inicial_heap: .quad 0

.section .text
.globl setup_brk, dismiss_brk, memory_alloc, memory_free, memory_mapping


# --------------------------------------------------------
# Nao ha utilizacao de registradores nesse procedimento
# Funcao recorrente, melhor modularizada
# --------------------------------------------------------
get_brk:                            
    pushq %rbp
    movq %rsp, %rbp

    movq $12, %rax
    movq $0, %rdi                    # Retorna o valor atual de brk
    syscall

    popq %rbp
    ret


# --------------------------------------------------------
# %rax - Retorno de get_brk (valor inicial de brk)
# --------------------------------------------------------
setup_brk:
    pushq %rbp
    movq %rsp, %rbp

    call get_brk                     # Pega o valor inicial de brk

    movq %rax, topo_inicial_heap     # Define a origem da Heap
    
    popq %rbp
    ret

# --------------------------------------------------------
# Nao ha utilizacao de registradores nesse procedimento
# --------------------------------------------------------
dismiss_brk: 
    pushq %rbp
    movq %rsp, %rbp

    movq $12, %rax                   # Altera brk
    movq topo_inicial_heap, %rdi     # Retorna o valor inicial de brk para zerar a heap
    syscall

    popq %rbp
    ret


# --------------------------------------------------------
# %r15 - Parametro (endereco a ser desalocado)
# %rbx - Registrador para percorrer a heap
# %rsi - Registrador para uso temporario
# --------------------------------------------------------
memory_free: 

    pushq %rbp
    movq %rsp, %rbp
    
    movq %rdi, %r15                  # Move o parametro (enredeco a ser liberado) para %r15
    
    cmpq %r15, topo_inicial_heap     # Compara se o endereco a ser desalocado esta antes do inicio do brk
    jg error

    call get_brk
    cmpq %rax, %r15                  # Compara se o endereco a ser desalocado esta depois do fim do brk
    jg error

    # --------------------------------------------------------

    movq topo_inicial_heap, %rbx     # Move o inicio da heap para o registrador que percorre a mesma

    memory_free_loop:                # Loop para verificar se o endereco a ser desalocado e valido
        
        addq HEADER, %rbx            # Soma header para alinhar com o endereco do parametro
        cmpq %r15, %rbx              # Compara endereco atual da heap com endereco passado por parametro
        jg error                     # Se ja passou do endereco entao e invalido
        je success                   # Se e exatamente entao o endereco e valido

        movq -8(%rbx), %rsi          # Move o tamanho do espaco alocado para uma variavel auxiliar
        addq %rsi, %rbx              # Soma somente o espaco alocado, chegando no header do proximo espaco

        jmp memory_free_loop

    # --------------------------------------------------------

    success:
        subq HEADER, %r15
        movq $0, (%r15)              # Marca o bloco como livre
        movq $1, %rax                # Retorno de sucesso
        jmp error_end

    # --------------------------------------------------------

    error:
        movq $0, %rax                # Retorno de erro

    # --------------------------------------------------------

    error_end:
    popq %rbp
    ret


# --------------------------------------------------------
# %r15 - Parametro (tamanho a ser alocado)
# %r14 - Menor valor encontrado (utilizado pelo best-fit)
# %r13 - Registrador do bloco repartido 
# %r12 - Endereco do bloco a ser utilizado 
# %r10 - Registradores com valores usados em comparacoes
# %r8  - Registrador para validar se encontrou um bloco ou nao
# %rcx - Endereco do topo da heap
# %rbx - Endereco do brk para percorrer a heap
# %rsi - Registrador auxiliar
# --------------------------------------------------------

memory_alloc: 
    pushq %rbp
    movq %rsp, %rbp

    movq %rdi, %r15                  # Move o parametro (tamanho a ser alocado) para %r15
    movq topo_inicial_heap, %rbx     # Move o topo para o registrador que percorre a heap

    call get_brk
    movq %rax, %rcx                  # Move o fim da heap para o registrador correto

    cmpq %rbx, %rcx                  # Verifica se a heap esta vazia
    je expand_heap                   # Se a heap esta vazia expande a mesma

# --------------------------------------------------------

    best_fit:
        movq $0, %r14                # Como comeca sem um bloco, maior bloco comeca com 0

        # --------------------------------------------------------

        while_search_empty_space:
            cmpq %rcx, %rbx          # Verifica se chegou ao fim da heap
            jge end_while_search_empty_space

            cmpq $1, (%rbx)          # Verifica se o espaco atual esta ocupado
            je find_next_block

            cmpq %r15, +8(%rbx)      # Compara se o espaco e suficiente, usando +8 para acessar o dado de tamanho sem acrescentar no endereco de %rbx
            jl find_next_block

            cmpq $0, %r14
            je end_new_alloc

            cmpq %r14, +8(%rbx)      # Compara se o valor atual e menor que o valor armazenado
            jge find_next_block

            end_new_alloc:
            movq +8(%rbx), %r14      # Se for menor marca como menor
            movq %rbx, %r12          # Salva o endereco do bloco que (provavelmente) sera utilizado

            # --------------------------------------------------------    

            find_next_block:
                addq $8, %rbx        # Move registrador para o tamanho do bloco
                movq (%rbx), %rsi    # Salva o tamanho do bloco em registrador temporario
                addq $8, %rbx        # Move para o inicio da secao de dados do bloco
                addq %rsi, %rbx      # Move o tamanho total da secao de dado
                jmp while_search_empty_space


        end_while_search_empty_space:
            cmpq $0, %r14            # Verifica se foi encontrado algum espaco
            je expand_heap           # Se nao encontrou aumenta a heap

# --------------------------------------------------------

    reuse_block:                        
    
        movq %r14, %rsi              # Move o tamanho para uma variavel auxiliar
        subq %r15, %rsi              # Subtrai o tamanho necessario do tamanho total
        
        cmpq $17, %rsi               # Se bloco for ate 16 bytes a mais só altera o estado e retorna o endereco
        jge repartition

        movq $1, (%r12)              # Marca bloco como ocupado

        addq $8, %r12                # Move para a secao de tamanho do bloco
        jmp end_allocation
    
# --------------------------------------------------------

    repartition:                     # Reparticiona em caso de 17 bytes ou mais sobrando
        
        movq %r12, %r13              # Manipula a reparticao no registrador %r13
        
        movq $1, (%r13)              # Marca o bloco com tamanho exato como ocupado
        addq $8, %r13
        movq %r15, (%r13)            # Define o novo tamanho do bloco
        addq $8, %r13                # Move mais oito bytes para poder alinhar o deslocamento

        
        addq %r15, %r13              # Desloca o endereco para o novo bloco a ser criado
        movq $0, (%r13)              # Marca o novo bloco como livre
        addq $8, %r13               
        movq %rsi, (%r13)            # Define o tamanho do novo bloco (diferenca do espaco livre pelo total usado)
        subq $16, (%r13)             # Diminui o tamanho que a header ocupa do tamanho dos dados

        addq $8, %r12                # Move para a secao de tamanho do bloco
        jmp end_allocation

# --------------------------------------------------------

    expand_heap:                     # Se nao existe bloco que comporta aumenta a brk serve para heap vazia a mesma logica

        movq %rbx, %r12              # Move o valor inicial no registrador correto
        addq HEADER, %rbx            # Adiciona o tamanho da header 
        addq %r15, %rbx              # Adiciona o numero de bytes a ser alocado

        movq $12, %rax
        movq %rbx, %rdi              # Atualiza o endereco de brk
        syscall

        movq $1, (%r12)              # Marca bloco como utilizado
        addq $8, %r12                # Move para a secao de tamanho do bloco
        movq %r15, (%r12)            # Define o tamanho utilizado pelo bloco

# --------------------------------------------------------

    end_allocation:
        movq %r12, %rax              # Manda o endereco salvo para o registrador de retorno
        addq $8, %rax                # Alinha corretamente com o inicio da secao de dados

        popq %rbp
        ret

