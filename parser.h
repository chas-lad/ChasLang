#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef struct Node {
    char *value;
    TokenType type;
    struct Node *right;
    struct Node *left;
} Node;

Token *parser(Token *tokens);
void print_tree(Node *node);
Node *init_node(Node *node, char *value, TokenType type);
void print_error(char *message);

#endif
