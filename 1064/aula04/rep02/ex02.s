.section .data
  A: .quad 0
.section .text
.global _start
_start:
  movq A, %rdi
_inicio:
  cmp $255, %rdi
  je _fim_w
  addq $1, %rdi
  jmp _inicio
_fim_w:
  movq %rdi, A
  movq $60, %rax
  syscall


