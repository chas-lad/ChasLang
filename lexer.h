#ifndef LEXER_H
#define LEXER_H

typedef enum {
    BEGINNING,
    INT,
    KEYWORD,
    SEPERATOR,
    OPERATOR,
    IDENTIFIER,
    END_OF_TOKENS
} TokenType;

typedef struct {
    TokenType type;
    char *value;
} Token;

Token *generate_number(char *current, int *current_index);
Token *generate_keyword_or_identifier(char *current, int *current_index);
void print_token(Token token);
Token *lexer(FILE *file);
Token *generate_seperator_or_operator(char *current, int *current_index, TokenType type);


#endif