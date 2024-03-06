# ChasLang

- Steps: Source code -> compiler -> assembler -> Object code -> Linker -> executable file
(I am focusing on compiler for this project!)



- Lexer does tokenisation (recognises words that make up the language)
- Parser recognises the structure and grammar - checks code provided is syntactically correct.
- Code generator scans AST(Asymmetric Syntax Tree) to produce assembly code.

- I would used LLVM to take our AST and generate Intermediate representation (IR) to make this language platform agnostic. However LLVM has little documentation on working with C and getting it to work proved difficult. Furtheremore, generating assembly manually proves to be interesting - so why not.

- Mac assembly generation instructions:
- Sadly, MacOS syscall numbers are not the same as in Linux. I used the file `syscalls.master`, located in this repository to help with assembly code comparison. IMPORTANT `0x02000000` has to be added to each of the system call numbers in order to use them in our asm files. 

- Assembler: `nasm -f macho64 -o test.o test.asm`
- Linker:    `clang -o test test.o -e _start` (specifying the entry point as _start for MacOS)


- No need for all the fancy setup C requires.

- dynamic type recognition