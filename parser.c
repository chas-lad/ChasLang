#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "lexer.h"

typedef struct {
    int value;
} NodeData;

typedef struct
{

} NodeStatement;

typedef struct {
    char *value;
    struct Node *right;
    struct Node *left;
} Node;

void print_tree(Node *node){
    if(node == NULL){
        return;
    }
    for(size_t i = 0; node->value[i] != NULL; i++){
        printf("%c", node->value[i]);
    }
    printf("\n");
    print_tree(node->left);
    print_tree(node->right);
}

Node *init_node(Node *node, char *value){
    node = malloc(sizeof(Node));
    node->value = malloc(sizeof(char) * 2);
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Token *parser(Token *tokens){
    Token *current_token = &tokens[0];
    Node *root = malloc(sizeof(Node));
    Node *left = malloc(sizeof(Node));
    Node *right = malloc(sizeof(Node));

    root = init_node(root, "HEY");
    left = init_node(left, "THERE");
    right = init_node(right, "WORLD");

    root->left = left;
    root->right = right;

    print_tree(root);   

    while(current_token->type != END_OF_TOKENS){
        if(current_token->type == INT){
            printf("INT: %s\n", current_token->value);
        }
        if(current_token->type == KEYWORD){
            printf("KEYWORD: %s\n", current_token->value);
        }
        if(current_token->type == SEPERATOR){
            printf("SEPERATOR: %s\n", current_token->value);
        }
        current_token++;
    }
    return current_token;
}