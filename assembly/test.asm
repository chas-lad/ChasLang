section .text
    global _start   ; Entry point symbol

_start:
    mov rax, 0x02000001  ; Syscall number for exit (0x2000001 for macOS)
    mov rdi, 1           ; Exit status 1
    syscall               ; Invoke syscall
