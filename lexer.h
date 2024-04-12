#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
    Token types:
    0. default
    1. LPAREN
    2. RPAREN
    3. PLUS
    4. MINUS
    5. MUL
    6. DIV
    7. MOD
    8. POWER
    9. INT
    10. FLOAT
*/


struct token{
    char *lexeme;
    int tokenType;
} typedef Token;


int typeNum(char c){
    switch(c){
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return 1;

        default:
            return 0;
    };
}


int typeOp(char c){
    switch(c){
        case '+':
            return 3;
        case '-':
            return 4;
        case '*':
            return 5;
        case '/':
            return 6;
        case '%':
            return 7;
        case '^':
            return 8;
        default:
            return 0;
    };
}

int typeParen(char c){
    switch(c){
        case '(':
            return 1;
        case ')':
            return 2;
        default:
            return 0;
    };
}

int typeSpace(char c){
    switch(c){
        case ' ':
        case '\t':
        case '\r':
        case '\n':
            return 1;
        default:
            return 0;
    };
}

//funcao que remove i caracteres do buffer
void removeChar(char *buffer, int i){
    int j = 0;
    while(buffer[j+i] != '\0'){
        buffer[j] = buffer[j+i];
        j++;
    }
    buffer[j] = '\0';
}

char* lex(Token *t, char *input){
    static char *buffer;

    if (input != NULL){
        buffer = strdup(input);
    }
    else{
        return NULL;
    }
    int i = 0;
    while(typeSpace(buffer[0])){
        //remove do buffer buffer[i] i vezes
        removeChar(buffer, i);

        i++;
    }
    i=0;
    if(typeNum(buffer[0])){
        //numero pode ser mais de um caractere ent devemos contar quantos sao para alocarmos corretamente
        while(typeNum(buffer[i])){
            if(buffer[i+1] == '.' && typeNum(buffer[i+2])){

                i++;
            }
            i++;
        }

        t->lexeme = (char*)malloc(sizeof(char)*i);
        strncpy(t->lexeme, buffer, (size_t) i);
        removeChar(buffer, i);

        //iterar atraves do buffer para verificar se o numero é float
        i = 0;
        while(t->lexeme[i] != '\0'){
            if(t->lexeme[i] == '.'){
                t->tokenType = 10;
                return buffer;
            }
            i++;
        }
        //se nao for float, é int
        t->tokenType = 9;
        return buffer;
    }

    if(typeOp(buffer[0])){
        t->tokenType = typeOp(buffer[0]);
        t->lexeme = (char*)malloc(sizeof(char));
        strncpy(t->lexeme, buffer, 1);
        removeChar(buffer, 1);

        return buffer;

    }

    if(typeParen(buffer[0])){
        t->tokenType = typeParen(buffer[0]);
        t->lexeme = (char*)malloc(sizeof(char));
        strncpy(t->lexeme, buffer, 1);
        removeChar(buffer, 1);

        return buffer;
    }

    t->tokenType = 0;
    return buffer;
}

Token expression(){
    char *input = "3 + 2";
    Token *t = (Token*)malloc(sizeof(Token));

    input = lex(t, input);
    printf("input: %s\n", input);
    while(input[0] != '\0'){
        input = lex(t, input);
        printf("Tipo: %d -> Digito: %s\n", t->tokenType, t->lexeme);
    }
}