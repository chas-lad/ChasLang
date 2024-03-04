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
}

Token *lexer(FILE *file){
    // Read entire file into a buffer first
    char *buffer = 0;
    fseek(file, 0, SEEK_END);
    int length = ftell(file); // get the length of the file
    fseek(file, 0, SEEK_SET);
    buffer = malloc(sizeof(char) * length);
    fread(buffer, 1, length, file);
    fclose(file);
    buffer[length + 1] = '\0'; // null terminate the buffer
    char *current = malloc(sizeof(char) * length + 1);
    current = buffer;
    int current_index = 0;

    Token *tokens = malloc(sizeof(Token) * 12); // allocate memory for 10 tokens
    size_t token_index = 0;

    while (current[current_index] != '\0'){ 
        char currentChar = current[current_index];
        if(currentChar == ';'){
            Token *semicolon_token = malloc(sizeof(Token));
            // need to allocate memory for the value of the token as well!
            semicolon_token->value = malloc(2 * sizeof(char)); // Allocate memory for two characters (one for the semicolon, one for the null terminator)
            semicolon_token->value[0] = current[current_index];
            semicolon_token->value[1] = '\0';
            semicolon_token->type = SEPERATOR;
            tokens[token_index] = *semicolon_token;
            token_index++;
        }else if(currentChar == '('){
            Token *open_paren_token = malloc(sizeof(Token));
            open_paren_token->value = malloc(2 * sizeof(char)); // Allocate memory for two characters (one for the semicolon, one for the null terminator)
            open_paren_token->value[0] = currentChar;
            open_paren_token->value[1] = '\0';
            open_paren_token->type = SEPERATOR;
            tokens[token_index] = *open_paren_token;
            token_index++;
        }else if(currentChar == ')'){
            Token *close_paren_token = malloc(sizeof(Token));
            close_paren_token->value = malloc(2 * sizeof(char)); // Allocate memory for two characters (one for the semicolon, one for the null terminator) 
            close_paren_token->value[0] = currentChar;
            close_paren_token->value[1] = '\0';
            close_paren_token->type = SEPERATOR;
            tokens[token_index] = *close_paren_token;
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
        }else{
            printf("ERROR: Unrecognized character: %c\n", currentChar);
            exit(1);
        }

        current_index++;
    } 
    tokens[token_index].value = '\0'; // null terminate the array of tokens
    tokens[token_index].type = END_OF_TOKENS;
    return tokens;
}
