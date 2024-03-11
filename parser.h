#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef struct Node {
    char *value;
    TokenType type;
    struct Node *right;
    struct Node *left;
} Node;

Node *parser(Token *tokens);
void print_tree(Node *node, int depth, char* side);
Node *init_node(Node *node, char *value, TokenType type);
void print_error(char *message);

#endif
