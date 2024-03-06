#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "parser.h"


// Important to note that the parser checked that the code is already syntactically correct
// When printing assembly code to file, tabs are two spaces!
void traverse_tree(Node *node, int is_left, FILE *file){
    if(node == NULL){
        return;
    }
    if(strcmp(node->value, "EXIT") == 0){
        fprintf(file, "  mov rax, 0x02000001\n");
    }
    if(strcmp(node->value, "(") == 0){
        printf("OPEN\n");
    }
    if(node->type == INT){
        fprintf(file, "  mov rdi, %s\n", node->value);
    }
    if(node->type == ")"){
        printf("KEYWORD %s\n", node->value);
    }
    if(strcmp(node->value, ";") == 0){
        fprintf(file, "  syscall");
    }
    if(is_left){

    }else{

    }

    for(size_t i = 0; node->value[i] != '\0'; i++){
        printf("%c", node->value[i]);
    }
    printf("\n");
    traverse_tree(node->left, 1, file);
    traverse_tree(node->right, 0, file);
}

int generate_code(Node *root){
    FILE *file = fopen("generated.asm", "w");
    assert(file != NULL && "File could not be opened");

    fprintf(file, "section .text\n");
    fprintf(file, "  global _start\n\n");
    fprintf(file, "_start:\n");
    // print_tree(root);

    traverse_tree(root, 0, file);
    fclose(file); // need to close the file before we can run assembler and linker
    return 0;
}
