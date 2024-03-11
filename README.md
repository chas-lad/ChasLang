# ChasLang

- Steps: Source code -> compiler -> assembler -> Object code -> Linker -> executable file
(I am focusing on compiler for this project!)

- Lexer does tokenisation (recognises words that make up the language)
- Parser recognises the structure and grammar - checks code provided is syntactically correct and produces AST.
- Code generator scans AST(Asymmetric Syntax Tree) to produce assembly code.
- The AST node titled PROGRAM will always be the root node. 

- I would have used LLVM to take our AST and generate Intermediate Representation (IR) code to make this language platform agnostic. However LLVM has little documentation on working with C and getting it to work proved difficult. Furtheremore, generating assembly manually proves to be interesting... - so why not.

- Mac assembly generation instructions (I use a Mac):
- Sadly, MacOS syscall numbers are not the same as in Linux. I used the file `syscalls.master`, located in this repository to help with assembly code comparison. IMPORTANT `0x02000000` has to be added to each of the system call numbers in order to use them in our asm files. 

- Assembler command: `nasm -f macho64 -o test.o test.asm`
- Linker command:    `clang -o test test.o -e _start` (specifying the entry point as _start for MacOS)

### TODO
- Support for char data type
- Need to implement correct order of operations
- Add some advanced maths operations e.g. squaring, square root.
- Add objects?
- Add hash table (similar methods to python dictionary). C doesn't have this functionality built in.
- Keep track of which line I am on when parsing to generate line number in syntax error. 
