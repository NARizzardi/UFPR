.section .data
  i: .quad 0
  m: .quad 0
  v: .quad 10, 30, 5, 100, 50

.section .text
.global _start
_start:
  movq  i, %rax
  movq  m, %rdi

_inicio_w:
  cmp  $5, %rax
  je   _fim_prog
  cmp  %rdi, v(,%rax,8)
  jle  _fim_if
  movq v(,%rax, 8), %rdi

_fim_if:
  addq $1, %rax
  jmp _inicio_w

_fim_prog:
  movq %rdi, m
  movq $60, %rax
  syscall
