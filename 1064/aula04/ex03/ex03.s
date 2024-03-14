.section .data
  X: .quad 80
  Y: .quad 82
.section .text
.global _start
_start:
  movq X, %rax
  movq $0, %rdi 
  cmp Y, %rax
  jge _fim_prog

_inicio_w:
  cmp Y, %rax
  jg _fim_while
  addq %rax, %rdi
  addq $1, %rax
  jmp _inicio_w

_fim_while:
  cmp $255, %rdi
  jle _fim_prog
  movq $255, %rdi
  
_fim_prog:
  movq $60, %rax
  syscall

  
