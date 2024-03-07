section .text
  global _start

_start:
  xor rax, rax
  xor rbx, rbx
  xor rcx, rcx
  xor rdx, rdx
  xor rsi, rsi
  xor rdi, rdi
  xor r8, r8
  xor r9, r9
  xor r10, r10
  xor r11, r11
  xor r12, r12
  xor r13, r13
  xor r14, r14
  xor r15, r15
  mov rax, 0x02000001
  mov rdi, 5
  sub rdi, 2
  add rdi, 3
  sub rdi, 1
  syscall