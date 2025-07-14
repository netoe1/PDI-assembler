#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>
#include <stdbool.h>
#include "debug-modules.h"
#include "instruction-set.h"
#include "utils.h"

#define FILE_TO_ASM "teste.forg"
#define LINE_LIMIT 256

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
    char line[LINE_LIMIT];
    char *instruction = NULL;
    char *reg = NULL;
    char *valStr = NULL;
    int val;
    int lineRead = 0;

    while (fgets(line, sizeof(line), openedFile) != NULL)
    {
        sanitize_buffer(line);
        lineRead++;
        if (line[0] == '\n' || line[0] == '#' || is_line_empty(line))
        {
            continue;
        }

        instruction = strtok(line, " ");
        if (!instruction) // Verifica se o strtok() foi concluído com sucesso
        {
            fprintf(stderr, "[LINE %d][ERR]: Erro ao dar parse na instrução!\n", lineRead);
            continue;
        }
        sanitize_buffer(instruction);
        to_lower(instruction);

        int instr_return = getInstructionByLabel(instruction); // Verifica se a opção existe no map

        if (instr_return == FAILURE_OPERATION)
        {
            fprintf(stderr, "[LINE %d][ERR]: A instrução '%s' não existe na arquitetura.\n", lineRead, instruction);
            continue;
        }

        if (strcmp(I_LDA_LABEL, instruction) == 0 || strcmp(I_STA_LABEL, instruction) == 0)
        {

            reg = strtok(NULL, ", \n");

            if (!reg || strlen(reg) == 0)
            {
                fprintf(stderr, "[LINE %d][ERR]: Faltando registrador na instrução '%s'.\n", lineRead, instruction);
                continue;
            }
            sanitize_buffer(reg);
            int regn = getRegByLabel(reg);
            if (regn == FAILURE_OPERATION)
            {
                fprintf(stderr, "[LINE %d][ERR]: Registrador '%s' não existe.\n", lineRead, reg);
                continue;
            }

            valStr = strtok(NULL, " \n");
            sanitize_buffer(instruction);

            if (!valStr || strlen(valStr) == 0)
            {
                fprintf(stderr, "[LINE %d][ERR]: Valor imediato ausente após registrador '%s'.\n", lineRead, reg);
                continue;
            }

            if (!is_number(valStr))
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
            print_debug_typeI(instruction, lineRead, reg, val);
            continue;
        }

        if (strcmp(R_SUB_LABEL, instruction) == 0 || strcmp(R_MUL_LABEL, instruction) == 0 || strcmp(R_SUM_LABEL, instruction) == 0) // Instrução TIPO R
        {
            // Não está pronto!
            char *rd = "teste";
            char *rf1 = "teste";
            char *rf2 = "teste";
            print_debug_typeR(instruction, lineRead, rd, rf1, rf2);
            continue;
        }

        if (strcmp(J_JMP_LABEL, instruction) == 0) // Instrução TIPO J
        {
            char *mem_address = strtok(NULL, " \n");
            if (!is_number(mem_address))
            {
                fprintf(stderr, "[LINE %d][ERR]: Valor '%s' não é um endereço de memória válido.\n", lineRead, valStr);
                continue;
            }

            int mem_address_int = atoi(mem_address);
            if (mem_address_int < 0 || mem_address_int > MAX_PROGRAM_MEM_SIZE)
            {
                fprintf(stderr, "[LINE %d][ERR]: O valor está fora do limite para a memória de programa.\n", lineRead);
                continue;
            }
            print_debug_typeJ(instruction, lineRead, mem_address_int);
            continue;
        }

        if (strcmp(B_BEQ_LABEL, instruction) == 0 || strcmp(B_BNE_LABEL, instruction) == 0) // Instrução TIPO B
        {
            char *r1 = "teste";
            char *r2 = "teste";
            int mem_address_int = 0;
            print_debug_typeB(instruction, lineRead, r1, r2, mem_address_int);
            continue;
        }
    }
}

int main(void)
{
    FILE *f = fopen(FILE_TO_ASM, "r");
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