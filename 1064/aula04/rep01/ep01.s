.section .text
.global _start
_start:
  movq $0, %rdi
_inicio_w:
  cmp $255, %rdi
  je _fim
  addq $1, %rdi
  jmp _inicio_w
_fim:
  movq $60, %rax
  syscall


