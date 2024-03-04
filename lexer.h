#ifndef LEXER_H
#define LEXER_H

typedef enum {
    INT,
    KEYWORD,
    SEPERATOR,
    END_OF_TOKENS
} TokenType;

typedef struct {
    TokenType type;
    char *value;
} Token;

Token *generate_number(char *current, int *current_index);
Token *generate_keyword(char *current, int *current_index);
void print_token(Token token);
Token *lexer(FILE *file);
Token *generate_seperator(char *current, int *current_index);


#endif