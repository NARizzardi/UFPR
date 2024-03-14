.section .data
 idade: .quad 18
.section .text
.global _start
_start: 
  movq idade, %r8
  cmp $18, %r8
  jl _else
  movq $1, %rdi
  jmp _fim_prog
_else: 
  movq $0, %rdi
_fim_prog:
  movq $60, %rax
  syscall
  
