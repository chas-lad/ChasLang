#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "lexer.h"


int main() {
    FILE *file;
    file = fopen("test.chas", "r");

    Token *tokens = lexer(file);
    for(int i = 0; tokens[i].type != END_OF_TOKENS; i++){
        print_token(tokens[i]);
    }
}