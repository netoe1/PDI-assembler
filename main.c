#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>
#include <stdbool.h>
#include "instruction-set.h"
#include "utils.h"

#define FILENAME_TO_ASSEMBLE "teste.forg"
void loadfile(char *filename)
{
    FILE *f = fopen(filename, "r");

    if (!f)
    {
        fprintf(stderr, "[arqerr]: Cannot open .arq file.");
        exit(-1);
    }
}

void parseFile(FILE *openedFile)
{
    char line[256];
    char *instruction = NULL;
    char *reg = NULL;
    char *valStr = NULL;
    int val;
    int lineRead = 0;
    while (fgets(line, sizeof(line), openedFile) != NULL)
    {
        sanitize_buffer(line);
        lineRead++;
        if (line[0] == '\n' || line[0] == '#')
        {
            continue;
        }

        instruction = strtok(line, " "); // Separa em tokens
        sanitize_buffer(instruction);
        to_lower(instruction);
        // Coloca tudo em minúsculo
        if (!instruction) // Verifica se o strtok() foi concluído com sucesso
        {
            fprintf(stderr, "[LINE %d][ERR]: Erro ao dar parse na instrução!\n", lineRead);
            continue;
        }

        // if (strlen(instruction) != MAX_INSTRUCTION_LABEL_SIZE) // Verifica se a instrução é válida com o tamanho do label
        // {
        //     fprintf(stderr, "[forg-mount-instr][LINE %d][ERR]: Instrução com tamanho inválido, as labels devem conter apenas 3 letras!\n", lineRead);
        //     exit(EXIT_FAILURE);
        // }

        int instr_return = getInstructionByLabel(instruction); // Verifica se a opção existe no map

        if (instr_return == FAILURE_OPERATION)
        {
            fprintf(stderr, "[LINE %d][ERR]: A instrução '%s' não existe na arquitetura.\n", lineRead, instruction);
            continue;
        }

        // If para detectar de que tipo é a expressão.

        if (strcmp(I_LDA_LABEL, instruction) == 0 || strcmp(I_STA_LABEL, instruction) == 0)
        {
            // 1. Captura registrador
            reg = strtok(NULL, ", \n");
            sanitize_buffer(instruction);
            if (!reg || strlen(reg) == 0)
            {
                fprintf(stderr, "[LINE %d][ERR]: Faltando registrador na instrução '%s'.\n", lineRead, instruction);
                continue;
            }

            if (strlen(reg) != MAX_REG_LABEL_SIZE)
            {
                fprintf(stderr, "[LINE %d][ERR]: Registrador '%s' inválido! Deve ter exatamente 2 letras.\n", lineRead, reg);
                continue;
            }

            int regn = getRegByLabel(reg);
            if (regn == FAILURE_OPERATION)
            {
                fprintf(stderr, "[LINE %d][ERR]: Registrador '%s' não existe.\n", lineRead, reg);
                continue;
            }

            // 2. Captura valor imediato
            valStr = strtok(NULL, " \n");
            sanitize_buffer(instruction);
            if (!valStr || strlen(valStr) == 0)
            {
                fprintf(stderr, "[LINE %d][ERR]: Valor imediato ausente após registrador '%s'.\n", lineRead, reg);
                continue;
            }

            if (!is_number(valStr)) // Se tiver implementado essa função em utils.h
            {
                fprintf(stderr, "[LINE %d][ERR]: Valor '%s' não é um número válido.\n", lineRead, valStr);
                continue;
            }

            val = atoi(valStr);
            if (val < 0 || val > MAX_IMED_TYPE_I_SIZE)
            {
                fprintf(stderr, "[LINE %d][ERR]: Valor imediato fora do intervalo permitido: %d\n", lineRead, val);
                continue;
            }
            printf("\nParse na linha:%d\n", lineRead);
            printf("Instrução: %s\n", instruction);
            printf("Registrador: %s\n", reg);
            printf("Imediato: %d\n", val);
            continue;
        }
        if (strcmp(R_SUB_LABEL, instruction) == 0 || strcmp(R_MUL_LABEL, instruction) == 0 || strcmp(R_SUM_LABEL, instruction) == 0) // Instrução TIPO R
        {
        }

        if (strcmp(J_JMP_LABEL, instruction) == 0) // Instrução TIPO J
        {
        }

        if (strcmp(B_BEQ_LABEL, instruction) == 0 || strcmp(B_BNE_LABEL, instruction) == 0) // Instrução TIPO B
        {
        }
    }
}

int main(void)
{
    FILE *f = fopen("teste.forg", "r");
    if (!f)
    {
        goto file_close;
    }

    parseFile(f);

file_close:
    if (f)
    {
        fclose(f);
    }
}