nasm -f macho64 -o test.o test.asm
clang -o test test.o -e _start