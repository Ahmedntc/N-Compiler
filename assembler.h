#include "neansim.h"

void cleanLine(char *linha){
    for(int i = 0; i < strlen(linha); i++){
        
        if(linha[i] == ' '){
            if(i == 0){
                for(int j = i; j < strlen(linha); j++){
                    linha[j] = linha[j+1];
                }
                i--;
            }
        }
        
        if(linha[i] == ' '){
            if(linha[i+1] == ' '){
                for(int j = i; j < strlen(linha); j++){
                    linha[j] = linha[j+1];
                }
                i--;
            }
        }

        if(linha[i] == '\n'){
            linha[i] = '\0';
        }
    }
}

void assemble(){
    //int ACC = 0;
    FILE *arquivo;
    uint16_t mem[256] = {0};

    char *linha = NULL;
    size_t tamanho = 0;

    int ins = 0;
    arquivo = fopen("program.asm", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
    }
    int ind = 0;
   // Lê o arquivo linha por linha
    while (getline(&linha, &tamanho, arquivo) != -1) {
        cleanLine(linha);
        printf("%s\n", linha);
        //splita linha
        char *token = strtok(linha, " ");
        for(int i = 0; i < strlen(linha); i++){
            if(token == NULL){
                break;
            }
            //ignora comentarios
            if(linha[i] == ';'){
                break;
            }
            if(strcmp(token, "DB") == 0){
                token = strtok(NULL, " ");
                int val = atoi(token);
                token = strtok(NULL, " ");
                int end = atoi(token);
                mem[end] = val;
                
            }
            if(strcmp(token, "STA") == 0){
                mem[ind] = 0x10;
                ind++;
                token = strtok(NULL, " ");
                int end = atoi(token);
                mem[ind] = end;
                //mem[end] = ACC;
                ind++;
            }
            if(strcmp(token, "LDA") == 0){
                mem[ind] = 0x20;
                ind++;
                token = strtok(NULL, " ");
                int end = atoi(token);
                mem[ind] = end;
                //ACC = mem[end];
                ind++;

            }
            if(strcmp(token, "ADD") == 0){
                mem[ind] = 0x30;
                ind++;
                token = strtok(NULL, " ");
                int end = atoi(token);
                mem[ind] = end;
                //ACC += mem[end];
                ind++;
            }
            if(strcmp(token, "OR") == 0){
                mem[ind] = 0x40;
                ind++;
                token = strtok(NULL, " ");
                int end = atoi(token);
                mem[ind] = end;
                ind++;
            }
            if(strcmp(token, "OR") == 0){
                mem[ind] = 0x40;
                ind++;
                token = strtok(NULL, " ");
                int end = atoi(token);
                mem[ind] = end;
                ind++;

            }
            if(strcmp(token, "AND") == 0){
                mem[ind] = 0x50;
                ind++;
                token = strtok(NULL, " ");
                int end = atoi(token);
                mem[ind] = end;
                ind++;

            }

            if(strcmp(token, "NOT") == 0){
                mem[ind] = 0x60;
                ind++;

            }
            if(strcmp(token, "JMP") == 0){
                mem[ind] = 0x70;
                ind++;
                token = strtok(NULL, " ");
                int end = atoi(token);
                mem[ind] = end;
                ind++;
            }
            if(strcmp(token, "JN") == 0){
                mem[ind] = 0x80;
                ind++;
                token = strtok(NULL, " ");
                int end = atoi(token);
                mem[ind] = end;
                ind++;
            }
            if(strcmp(token, "JZ") == 0){
                mem[ind] = 0x90;
                ind++;
                token = strtok(NULL, " ");
                int end = atoi(token);
                mem[ind] = end;
                ind++;
            }

            if(strcmp(token, "HLT") == 0){
                mem[ind] = 0xF0;
                ind++;
            }
            token = strtok(NULL, " ");
        }   
    }
    //print mem
    for(int i = 0; i < 256; i++){
        printf("%d ", mem[i]);
    }

    fclose(arquivo);
    free(linha);

    FILE *file;
    file = fopen("out.mem", "wb");
    if (file == NULL) {
        perror("Error  ");
    }
    //write header first four bytes
    uint8_t header[4] = {3, 78, 68, 82};
    fwrite(header, sizeof(uint8_t), 4, file);
    //write mem
    fwrite(mem, sizeof(uint16_t), 256, file);
    fclose(file);
    emula();


}