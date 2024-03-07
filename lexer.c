#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "lexer.h"

// function to continue generating a number token once we have found the first digit in a sequence
// (use pointer for current index to keep track of where we are in the buffer without having to return it)
Token *generate_number(char *current, int *current_index){
    Token *token = malloc(sizeof(Token));
    token->type = INT; // for now we presume always INT
    char *value = malloc(sizeof(char) * 8);
    int value_index = 0;
    while(isdigit(current[*current_index]) && current[*current_index] != '\0'){
        if(!isdigit(current[*current_index])){
            break;
        }
        value[value_index] = current[*current_index];
        value_index++;
        *current_index += 1;
    }
    value[value_index] = '\0';  // null terminate the string
    token->value = value;
    return token;
}

// function to continue generating a keyword token once we have found the first letter in a sequence
Token *generate_keyword(char *current, int *current_index){
    Token *token = malloc(sizeof(Token));
    char *keyword = malloc(sizeof(char) * 8);
    int keyword_index = 0;
    while(isalpha(current[*current_index]) && current[*current_index] != '\0'){
        keyword[keyword_index] = current[*current_index];
        keyword_index++;
        *current_index += 1;
    }
    keyword[keyword_index] = '\0';  // null terminate the string
    if (strcmp(keyword, "exit") == 0){
        token->type = KEYWORD;
        token->value = "EXIT";
    }
    return token;
}

//temporary helper function
void print_token(Token token){
    printf("TOKEN VALUE: ");
    for(int i = 0; token.value[i] != '\0'; i++){
        printf("%c", token.value[i]);
    }
    if(token.type == INT){
        printf(" Type: INT\n");
    }
    if(token.type == KEYWORD){
        printf(" Type: KEYWORD\n");
    }
    if(token.type == SEPERATOR){
        printf(" Type: SEPERATOR\n");
    }   
    if(token.type == OPERATOR){
        printf(" Type: OPERATOR\n");
    }
    if (token.type == END_OF_TOKENS){
        printf(" Type: END_OF_TOKENS\n");
    }
    if (token.type == BEGINNING){
        printf(" Type: BEGINNING\n");
    }

}

Token *lexer(FILE *file){
    // Read entire file into a buffer first
    char *current = 0;
    fseek(file, 0, SEEK_END);
    int length = ftell(file); // get the length of the file
    fseek(file, 0, SEEK_SET);
    current = malloc(sizeof(char) * length + 1);
    fread(current, 1, length, file);
    fclose(file);

    current[length + 1] = '\0'; // null terminate the buffer
    int current_index = 0; // keep track of where we are in the buffer

    Token *tokens = malloc(sizeof(Token) * 1000); // allocate memory for 1000 tokens - TODO - make this dynamic
    size_t token_index = 0; // keep track of where we are in the array of tokens

    while (current[current_index] != '\0'){ 
        char currentChar = current[current_index];
        Token *token = NULL;

        if(currentChar == ';'){
            token = generate_seperator_or_operator(current, &current_index, SEPERATOR);
            tokens[token_index] = *token;
            token_index++;
        }else if(currentChar == '('){
            token = generate_seperator_or_operator(current, &current_index, SEPERATOR);
            tokens[token_index] = *token;
            token_index++;
        }else if(currentChar == ')'){
            token = generate_seperator_or_operator(current, &current_index, SEPERATOR);
            tokens[token_index] = *token;
            token_index++;
        }else if(currentChar == '+'){
            token = generate_seperator_or_operator(current, &current_index, OPERATOR);
            tokens[token_index] = *token;
            token_index++;
        } else if(currentChar == '-'){
            token = generate_seperator_or_operator(current, &current_index, OPERATOR);
            tokens[token_index] = *token;
            token_index++;
        }else if(currentChar == '*'){
            token = generate_seperator_or_operator(current, &current_index, OPERATOR);
            tokens[token_index] = *token;
            token_index++;
        }else if(currentChar == '/'){
            token = generate_seperator_or_operator(current, &current_index, OPERATOR);
            tokens[token_index] = *token;
            token_index++;
        }else if(isdigit(currentChar)){
            Token *integer_token = generate_number(current, &current_index);
            tokens[token_index] = *integer_token;
            token_index++;
            current_index--; // we need to go back one index to account for the increment in the generate_number function
        }else if(isalpha(currentChar)){
            Token *keyword_token = generate_keyword(current, &current_index);
            tokens[token_index] = *keyword_token;
            token_index++;
            current_index--; // we need to go back one index to account for the increment in the generate_keyword function
        }

        current_index++;
    } 
    // null terminate the array of tokens so we know when to stop when parsing. (alternative to keeping track of the length of the array of tokens)
    tokens[token_index].value = NULL; // null terminate the array of tokens
    tokens[token_index].type = END_OF_TOKENS;
    return tokens;
}


Token *generate_seperator_or_operator(char *current, int *current_index, TokenType type){
    Token *token = malloc(sizeof(Token));
    // need to allocate memory for the value of the token as well!
    token->value = malloc(2 * sizeof(char)); // Allocate memory for two characters (one for the semicolon, one for the null terminator)
    token->value[0] = current[*current_index];
    token->value[1] = '\0';
    token->type = type;

    return token;
}