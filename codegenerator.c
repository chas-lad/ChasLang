#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "parser.h"
#include "./hashmap/hashmap.h"


// How I want to deal with addition 
// void traverse_tree(Node *node, int is_left, FILE *file){
//     if(node == NULL){
//         return;
//     }
//     if(node->type == OPERATOR){
//         if(strcmp(node->value, "+") == 0){
//             traverse_tree(node->left, 1, file); // Traverse left subtree
//             traverse_tree(node->right, 0, file); // Traverse right subtree
//             fprintf(file, "  add rdi, %s\n", node->value); // Add operation
//         }
//     }
//     else if(node->type == INT){
//         fprintf(file, "  mov rdi, %s\n", node->value); // Move integer value into rdi
//     }
//     else if(strcmp(node->value, "EXIT") == 0){
//         fprintf(file, "  mov rax, 60\n"); // Syscall number for exit
//         fprintf(file, "  xor rdi, rdi\n"); // Exit status (0)
//         fprintf(file, "  syscall\n"); // Invoke syscall
//     }

//     traverse_tree(node->left, 1, file); // Traverse left subtree
//     traverse_tree(node->right, 0, file); // Traverse right subtree
// }


Node *generate_operator_code(Node *node, char* syscall_number ,FILE *file){
    if(strcmp(node->value, "=") == 0){
        fprintf(file, "  push %s\n", node->left->value);
        node->left = NULL;
        printf("EQUALS\n");
    }
    else{
        Node *tmp = node;
        fprintf(file, "  mov rax, %s\n", node->left->value);
        int did_loop = 0;
        while(tmp->right->type == OPERATOR){
            did_loop = 1;
            char *operator = search(tmp->value[0])->data;
            tmp = tmp->right;
            fprintf(file, "  mov rbx, %s\n", tmp->left->value);
            if(strcmp(operator, "mul") == 0 || strcmp(operator, "div") == 0){
                fprintf(file, "  %s rbx\n", operator);
                fprintf(file, "  mov rdi, rax\n"); 
            }
            else{
                fprintf(file, "  %s rax, rbx\n", operator);
                fprintf(file, "  mov rdi, rax\n");
            }
        }
        if(did_loop){
            if(tmp->value[0] == '*' || tmp->value[0] == '/'){
                fprintf(file, "  mov rax, rdi\n");
                fprintf(file, "  mov rbx, %s\n", tmp->right->value);
                fprintf(file, "  %s rbx\n", search(tmp->value[0])->data);
                fprintf(file, "  mov rdi, rax\n");
            }
            else{
                fprintf(file, "  %s rdi, %s\n", search(tmp->value[0])->data, tmp->right->value);
            }
        } else{
            fprintf(file, "  mov rbx, %s\n", tmp->right->value);
            fprintf(file, "  %s rbx\n", search(tmp->value[0])->data);
            fprintf(file, "  mov rdi, rax\n");
        }

        fprintf(file, "  mov rax, %s\n", syscall_number);
        fprintf(file, "  syscall\n");
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}


// Important to note that the parser checked that the code is already syntactically correct
// When printing assembly code to file, tabs are two spaces!
void traverse_tree(Node *node, int is_left, FILE *file, char* syscall_number){

    if(node == NULL){
        return;
    }

    if(strcmp(node->value, "EXIT") == 0){
        syscall_number = "0x02000001";
    }
    if(strcmp(node->value, "INT") == 0){
        // node->left = NULL;
    }
    if(strcmp(node->value, "(") == 0){

    }

    // Use our hashmap to find the correct assembly instruction for the operator
    if(node->type == OPERATOR){
        generate_operator_code(node, syscall_number, file);
    }

    if(node->type == INT){
        fprintf(file, "  mov rax, %s\n", syscall_number);
        fprintf(file, "  mov rdi, %s\n", node->value);
        fprintf(file, "  syscall\n");
    }
    if(node->type == IDENTIFIER){
        if(strcmp(syscall_number, "0x02000001") == 0){
                fprintf(file, "  mov rax, %s\n", syscall_number);
                fprintf(file, "  pop rdi\n"); 
                fprintf(file, "  syscall\n"); 
        } 

    }
    if(strcmp(node->value, ")") == 0){

    }
    if(strcmp(node->value, ";") == 0){
    
    }
    if(is_left){

    }else{

    }

    for(size_t i = 0; node->value[i] != '\0'; i++){
        printf("%c", node->value[i]);
    }
    printf("\n");
    traverse_tree(node->left, 1, file, syscall_number);
    traverse_tree(node->right, 0, file, syscall_number);
}

// set all our general purpose registers we are going to use to zero before we start
void zeroRegisters(FILE *file){
    fprintf(file, "  xor rax, rax\n");
    fprintf(file, "  xor rbx, rbx\n");
    fprintf(file, "  xor rcx, rcx\n");
    fprintf(file, "  xor rdx, rdx\n");
    fprintf(file, "  xor rsi, rsi\n");
    fprintf(file, "  xor rdi, rdi\n");
    fprintf(file, "  xor r8, r8\n");
    fprintf(file, "  xor r9, r9\n");
    fprintf(file, "  xor r10, r10\n");
    fprintf(file, "  xor r11, r11\n");
    fprintf(file, "  xor r12, r12\n");
    fprintf(file, "  xor r13, r13\n");
    fprintf(file, "  xor r14, r14\n");
    fprintf(file, "  xor r15, r15\n");
}

int generate_code(Node *root){
    insert('-', "sub");
    insert('+', "add");
    insert('*', "mul");
    insert('/', "div");

    FILE *file = fopen("generated.asm", "w");
    assert(file != NULL && "File could not be opened");

    fprintf(file, "section .text\n");
    fprintf(file, "  global _start\n\n");
    fprintf(file, "_start:\n");
    // print_tree(root);
    
    //display();

    zeroRegisters(file);

    traverse_tree(root, 0, file, "0");
    fclose(file); // need to close the file before we can run assembler and linker
    return 0;
}
