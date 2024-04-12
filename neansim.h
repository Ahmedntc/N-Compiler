#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

// simulador da maquina neander

void emula()
{
    // definir acumulador
    int ACC = 0;
    // definir program counter
    int PC = 0;
    // definir flags
    int N, Z = 0;
    FILE *file;
    uint8_t buffer[256];
    char header[4];

    file = fopen("out.mem", "rb");
    if (file == NULL)
    {
        perror("Error  ");
        return;
    }

    // armazena o header do neander (sempre os primeiros 4 bytes do arquivo mem)
    fread(&header, sizeof(char), 4, file);
    // armazena o conteudo do arquivo mem
    for (int i = 0; i < 256; i++)
    {
        // armazenar 2 bytes por vez ja que no neander sempre sao 1 byte por instrucao/endereço e mais um byte vazio e so depois a proxima instrucao/endereço
        uint16_t data;
        fread(&data, sizeof(uint16_t), 1, file);
        buffer[i] = (uint8_t)data;
        printf("%d ", buffer[i]);
    }
    fclose(file);
    int instrucao = 0;
    int end = 0;
    int r = 0;

    while (r != 1)
    {

        if (PC == 0)
        {
            Z = 1;
        }
        else
        {
            Z = 0;
        }
        if (ACC >= 128)
        {
            N = 1;
        }
        else
        {
            N = 0;
        }
        switch (buffer[PC])
        {
            // nop
            case 0:
                break;
            // sta
            case 16:
                PC++;
                end = buffer[PC];
                buffer[end] = ACC;
                break;
            // lda
            case 32:
                PC++;
                end = buffer[PC];
                ACC = buffer[end];
                break;
            // add
            case 48:
                PC++;
                end = buffer[PC];
                ACC = ACC + buffer[end];
                break;
            // or
            case 64:
                PC++;
                end = buffer[PC];
                ACC = ACC | buffer[end];
                break;
            // and
            case 80:
                PC++;
                end = buffer[PC];
                ACC = ACC & buffer[end];
                break;
            // not
            case 96:
                ACC = ~ACC;
                break;
            // jmp
            case 128:
                PC++;
                end = buffer[PC];
                PC = buffer[end];
                break;
            // jn
            case 144:
                PC++;
                if (N == 1)
                {
                    end = buffer[PC];
                    PC = buffer[end];
                }
                break;
            // jnz
            case 160:
                PC++;
                if (Z == 0)
                {
                    end = buffer[PC];
                    PC = buffer[end];
                }
                break;
            // hlt
            case 240:
                r = 1;

                break;
        }
        PC++;

    }


    printf("\nMaquina apos execução\n");
    for (int i = 0; i < 256; i++)
    {
        printf("%d ", buffer[i]);
    }
    printf("\n");
    printf("ACC: %d\n", ACC);
    printf("PC: %d\n", PC);
    printf("N: %d\n", N);
    printf("Z: %d\n", Z);
    

}
