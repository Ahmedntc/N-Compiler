#include "lexer.h"
#include "assembler.h"

void factor(Token *t);
void eval_exp2(Token *t);
void eval_exp(Token *t); 
int addrIndex = 128;
int type;
char *token;
bool lda = false;
int tokarr[128];
int tokarrIndex = 0;