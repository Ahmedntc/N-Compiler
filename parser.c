#include "parser.h"
char *input;

void eval_exp(Token *t)
{
    input = lex(t, input);
    eval_exp2(t);
}
void eval_exp2(Token *t)
{
    FILE *arquivo;
    arquivo = fopen("program.asm", "a");
    factor(t);
    while (t->tokenType == 3 || t->tokenType == 4)
    {
        type = t->tokenType;
        if (type == 3)
        {
            if(!lda){
                if(arquivo != NULL){
                    fseek(arquivo, 0, SEEK_END);
                    fprintf(arquivo, "LDA %d\n", tokarr[0]);
                }
                lda = true;
            }
            eval_exp(t);
        }
        else
        {
            printf("SUB\n");
        }
    }
    fclose(arquivo);
}

void factor(Token *t)
{
    FILE *arquivo;
    arquivo = fopen("program.asm", "a");
    if (t->tokenType == 9)
    {
        tokarr[tokarrIndex] = addrIndex;
        tokarrIndex++;
        //write into a file DB t->lexeme addrIndex
        if (arquivo != NULL)
        {
            fseek(arquivo, 0, SEEK_END);
            fprintf(arquivo, "DB %s %d\n", t->lexeme, addrIndex);
            addrIndex++;
        }

        printf("PUSH %s\n", t->lexeme);
        if(token == NULL){
            token = t->lexeme;
        }

        input = lex(t, input);


    }
    fclose(arquivo);
}

void main()
{
    FILE *arquivo;
    arquivo = fopen("program.asm", "w");
    if(arquivo == NULL){ 
        return;
    }
    fclose(arquivo);
    char buffer[128];
    printf("Enter an expression: ");
    fgets(buffer, sizeof(buffer), stdin);
    input = (char *)malloc(strlen(buffer) + 1);
    strcpy(input, buffer);

    Token *t = (Token *)malloc(sizeof(Token));
    eval_exp(t);

    arquivo = fopen("program.asm", "a");
    for (int i = 1; i < tokarrIndex; i++)
    {
        fprintf(arquivo, "ADD %d\n", tokarr[i]);
    }
    fprintf(arquivo, "HLT\n");
    fclose(arquivo);
    free(input);

    assemble();

}