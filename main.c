#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "lexer.h"
#include "parser.h"
#include "codegenerator.h"


int main(int argc, char *argv[]) {
    if (argc < 2){
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }
    FILE *file;
    file = fopen(argv[1], "r");

    Token *tokens = lexer(file);
    // for(int i = 0; tokens[i].type != END_OF_TOKENS; i++){
    //     print_token(tokens[i]);
    // }

    Node *test = parser(tokens);

    generate_code(test);
    FILE *assembly_file = fopen("generated.asm", "r");
    if(assembly_file == NULL){
        printf("Could not open file\n");
        exit(1);
    }

    system("nasm -f macho64 -o generated.o generated.asm");
    system("clang -o generated generated.o -e _start");
}