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

void print_tree(Node *node, int depth, char* side){
    if(node == NULL){
        return;
    }

    // Print spaces for each level of depth
    for(int i = 0; i < depth; i++){
        printf("  ");
    }

    // Print the node value and whether it's a left or right child
    printf("%s (%s child)\n", node->value, side);
    print_tree(node->left, depth + 1, "left");
    print_tree(node->right, depth + 1, "right");
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

Token *generate_operation_nodes(Token *current_token, Node *current_node){
    Node *oper_node = init_node(oper_node, current_token->value, OPERATOR);
    current_node->left->left = oper_node;
    current_node = oper_node;
    current_token--;
    Node *expr_node = init_node(expr_node, current_token->value, INT);
    current_node->left = expr_node;
    current_token++;
    current_token++;
    while(current_token->type == INT || current_token->type == OPERATOR){
        if(current_token->type == INT){
            if(current_token->type != INT || current_token->type == NULL){
                print_error("Invalid syntax on INT");
                exit(1);    
            }
            current_token++;
            if(current_token->type != OPERATOR){
                current_token--;
                Node *second_expr_node = init_node(second_expr_node, current_token->value, INT);
                current_node->right = second_expr_node;
            }

        }
        if(current_token->type == OPERATOR){
            Node *next_oper_node = init_node(next_oper_node, current_token->value, OPERATOR);
            current_node->right = next_oper_node;
            current_node = next_oper_node;
            current_token--;
            current_node->left = current_token;
            Node *second_expr_node = init_node(second_expr_node, current_token->value, INT);
            current_node->left = second_expr_node;
            current_token++;
        }
        current_token++;
    }
    return current_token;
}

void handle_exit_syscall(Node *root, Token *current_token, Node *current){
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
        if(current_token->type == INT || current_token->type == IDENTIFIER){ // in our exit call we can have either a variable or an integer
            current_token++;
            if(current_token->type == OPERATOR && current_token->type != NULL){
                current_token = generate_operation_nodes(current_token, current);
                current_token--;
            }
            else{
                current_token--;
                Node *expr_node = init_node(expr_node, current_token->value, current_token->type);
                current->left->left = expr_node;
            }
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

void handle_token_errors(char *error_text, Token *current_token, TokenType type){
    if(current_token->type == END_OF_TOKENS || current_token->type != type){
        print_error(error_text);
    }
}

Node *create_variables(Node *root, Token *current_token, Node *current){
    Node *var_node = init_node(var_node, current_token->value, KEYWORD); // e.g. this node would be a var node like INT
    current->left = var_node;
    current = var_node;
    current_token++;
    handle_token_errors("Invalid syntax after INT", current_token, IDENTIFIER);

    if(current_token->type == IDENTIFIER){
       Node *identifier_node = init_node(identifier_node, current_token->value, IDENTIFIER);
       current->left = identifier_node;
       current = identifier_node;
       current_token++;
    }
    handle_token_errors("Invalid syntax after identifier", current_token, OPERATOR);

    if(current_token->type == OPERATOR){
        if(strcmp(current_token->value, "=")){ // Remember strcmp returns 0 if the strings are equal and 1 if they are not!
            print_error("Invalid syntax on =\n");
        }
        Node *equal_node = init_node(equal_node, current_token->value, OPERATOR);
        current->left = equal_node;
        current = equal_node;
        current_token++;
    }

    handle_token_errors("Invalid syntax after equals", current_token, INT);
    
    if(current_token->type == INT){
        Node *expr_node = init_node(expr_node, current_token->value, INT);
        current->left = expr_node;
        current_token++;
    }

    handle_token_errors("Invalud syntax after expression", current_token, SEPERATOR);

    current = var_node;
    if(current_token->type == SEPERATOR && strcmp(current_token->value, ";") == 0){
        Node *semicolon_node = init_node(semicolon_node, current_token->value, SEPERATOR);
        current->right = semicolon_node;
        current = semicolon_node;
    }
    return current;
}

Node *parser(Token *tokens){
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

        switch(current_token->type){
            case KEYWORD:
                if(strcmp(current_token->value, "EXIT") == 0){
                    handle_exit_syscall(root, current_token, current);
                }
                if(strcmp(current_token->value, "INT") == 0){
                    current = create_variables(root, current_token, current);
                }
                break;

            case SEPERATOR:
                //
                break;
            case INT:
                //
                printf("INT\n");
                break;
            case IDENTIFIER:
                printf("IDENTIFIER\n");
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

    print_tree(root, 0, "root");

    return root;
}
