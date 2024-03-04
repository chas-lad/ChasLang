#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"

typedef enum {
    INT_LIT,
    STATEMENT,
    EXTRA,
    BEGINNING
} NodeTypes;

typedef struct Node {
    char *value;
    NodeTypes type;
    struct Node *right;
    struct Node *left;
} Node;

void print_tree(Node *node){
    if(node == NULL){
        return;
    }
    printf("%s\n", node->value);
    print_tree(node->left);
    print_tree(node->right);
}

Node *init_node(Node *node, char *value, NodeTypes type){
    node = malloc(sizeof(Node));
    node->value = malloc(sizeof(char) * 2);
    node->type = (int)type;
    strcpy(node->value, value);
    node->left = NULL;
    node->right = NULL;
    return node;
}

Token *parser(Token *tokens){
    // Check if tokens is NULL or empty
    if (tokens == NULL || tokens->type == END_OF_TOKENS) {
        fprintf(stderr, "No tokens provided\n");
        exit(EXIT_FAILURE);
    }

    Token *current_token = tokens;
    Node *root = NULL;
    Node *left = malloc(sizeof(Node));
    Node *right = malloc(sizeof(Node));
    root = init_node(root, "PROGRAM", BEGINNING);

    root->left = left;
    root->right = right;

    print_tree(root);   

    Node *current = root;

    // Assuming there's more parsing logic here
    while(current_token->type != END_OF_TOKENS){
        if(current == NULL){
            break;
        }
        if(current == root){
            //
        }

        if(current_token->type == KEYWORD && strcmp(current_token->value, "exit")){
            Node *exit_node = malloc(sizeof(Node));
            exit_node = init_node(exit_node, current_token->value, STATEMENT);
            root->right = exit_node;
            current = exit_node;
            current_token++;
            if(current_token->type != SEPERATOR){
                printf("ERROR\n");
                exit(1);
            }
            Node *open_paren_node = init_node(open_paren_node, current_token->value, EXTRA);
            current->left = open_paren_node;
            
            current_token++;

            Node *expr_node = init_node(expr_node, current_token->value, INT_LIT);  
            current->left->left = expr_node;

            current_token++;
            Node *close_paren_node = init_node(close_paren_node, current_token->value, EXTRA);
            current->left->right = close_paren_node;

            current_token++;

            Node *semicolon_node = init_node(semicolon_node, current_token->value, EXTRA);
            current->right = semicolon_node;

            printf("EXIT\n");
            break;
        }

        current_token++;
    }

    print_tree(root);
    
    return current_token;
}
