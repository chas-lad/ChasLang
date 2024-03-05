#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"



typedef struct Node {
    char *value;
    TokenType type;
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

Node *init_node(Node *node, char *value, TokenType type){
    node = malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed for node\n");
        exit(EXIT_FAILURE);
    }
    node->value = malloc(strlen(value) + 1); // Allocate memory for the string value
    if (node->value == NULL) {
        fprintf(stderr, "Memory allocation failed for value\n");
        exit(EXIT_FAILURE);
    }
    strcpy(node->value, value);
    node->type = type; // Assign the enum directly
    node->left = NULL;
    node->right = NULL;
    return node;
}

void print_error(char *message){
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}

Token *parser(Token *tokens){
    // Check if tokens is NULL or empty
    if (tokens == NULL || tokens->type == END_OF_TOKENS) {
        fprintf(stderr, "No tokens provided\n");
        exit(EXIT_FAILURE);
    }

    Token *current_token = tokens;
    Node *root = NULL;
    root = init_node(root, "PROGRAM", BEGINNING);


    Node *current = root;

    // Assuming there's more parsing logic here
    while(current_token->type != END_OF_TOKENS){
        if(current_token == NULL){
            printf("Current node is NULL\n"); // Debug print statement
            break;
        }
        if(current == root){
            //
        }

        switch(current_token->type){
            case KEYWORD:
                if(strcmp(current_token->value, "EXIT") == 0){
                    Node *exit_node = init_node(exit_node, current_token->value, KEYWORD);
                    root->right = exit_node;
                    current = exit_node;
                    current_token++;
                    if(current_token->type == END_OF_TOKENS){
                        print_error("Invalid syntax on OPEN");
                    }
                    if(strcmp(current_token->value, "(") == 0 && current_token->type == SEPERATOR){
                        Node *open_paren_node = init_node(open_paren_node, current_token->value, SEPERATOR);
                        current->left = open_paren_node;
                        current_token++;
                        if(current_token->type == END_OF_TOKENS){
                            print_error("Invalid syntax on INT");
                        }
                        if(current_token->type == INT){
                            Node *expr_node = init_node(expr_node, current_token->value, INT);
                            current->left->left = expr_node;
                            current_token++;
                            if(current_token->type == END_OF_TOKENS){
                                print_error("Invalid syntax on CLOSE");
                            }
                            if(strcmp(current_token->value, ")") == 0 && current_token->type == SEPERATOR){
                                Node *close_paren_node = init_node(close_paren_node, current_token->value, SEPERATOR);
                                current->left->right = close_paren_node;
                                current_token++;
                                if(current_token->type == END_OF_TOKENS){
                                    print_error("Invalid syntax on SEMI");
                                }
                                if(strcmp(current_token->value, ";") == 0 && current_token->type == SEPERATOR){
                                    Node *semicolon_node = init_node(semicolon_node, current_token->value, SEPERATOR);
                                    current->right = semicolon_node;
                                    break;
                                } else{
                                    print_error("ERROR: Incorrect Syntax on semicolon.\n");
                                }
                            } else {
                                print_error("ERROR: Incorrect Syntax on closing parenthesis.\n");
                            }
                        } else{
                            print_error("ERROR: Incorrect Syntax on integer.\n");
                        }
                    } else{
                        print_error("ERROR: Incorrect Syntax on opening parenthesis.\n");
                    }
                }
                break;

            case SEPERATOR:
                //
                break;
            case INT:
                //
                printf("INT\n");
                break;
            case BEGINNING:
                //
                break;
            case END_OF_TOKENS:
                //
                break;
        }

        current_token++;
    }
    printf("Done parsing\n");

    print_tree(root);

    return current_token;
}
