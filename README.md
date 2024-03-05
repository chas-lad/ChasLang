# ChasLang


- Lexer does tokenisation (recognises words that make up the language)
- Parser recognises the structure and grammar - uses Abstract Syntax Tree (AST) to give intermediate representation of source code as a tree structure.
- Source code -> FrontEnd(Parser and Lexer) -> AST(IR) -> Backend () -> Output

- Mac instructions:
- Sadly, MacOS syscall numbers are not the same as in Linux. I used the file `syscalls.master`, located in this repository to help with assembly code comparison. IMPORTANT `0x02000000` has to be added to each of the system call numbers in order to use them.

- Assembler: `nasm -f macho64 -o test.o test.asm`
- Linker:    `clang -o test test.o -e _start` (specifying the entry point as _start for MacOS)


- No need for all the fancy setup C requires.

- dynamic type recognition