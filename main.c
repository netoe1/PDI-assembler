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
            fprintf(stderr, "[LINE %d][ERR]: Instrução inválida / não processada.\nCheque a documentação dos tipos de instrução.\n", lineRead);
            continue;
        }
        sanitize_buffer(instruction);
        to_lower(instruction);
        // int instr_return = getInstructionByLabel(instruction); // Verifica se a opção existe no map
        InstructionMap instructionParsed = getInstructionStructData(instruction);

        if (strcmp(instructionParsed.code, "-1") == FAILURE_OPERATION)
        {
            fprintf(stderr, "[LINE %d][ERR]: A instrução '%s' não existe na arquitetura.\n", lineRead, instruction);
            continue;
        }

        // if (strcmp(I_LDA_LABEL, instruction) == 0 || strcmp(I_STA_LABEL, instruction) == 0)
        if (instructionParsed.type == TYPE_I)
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
            // continue;
        }

        else if (instructionParsed.type == TYPE_R) // Instrução TIPO R
        {
            char *rd = strtok(NULL, ",");
            if (!rd)
            {
                fprintf(stderr, "[LINE %d][ERR]: Registrador destino não definido\n", lineRead);
                continue;
            }

            char *rf1 = strtok(NULL, ",");
            if (!rf1)
            {
                fprintf(stderr, "[LINE %d][ERR]: Registrador fonte 1 não definido:\n", lineRead);
                continue;
            }

            char *rf2 = strtok(NULL, ",");
            if (!rf2)
            {
                fprintf(stderr, "[LINE %d][ERR]: Registrador fonte 2 não definido\n", lineRead);
                continue;
            }

            sanitize_buffer(rd);
            sanitize_buffer(rf1);
            sanitize_buffer(rf2);
            to_lower(rd);
            to_lower(rf1);
            to_lower(rf2);

            print_debug_typeR(instruction, lineRead, rd, rf1, rf2);

            if (getRegByLabel(rf1) == -1 || getRegByLabel(rf2) == -1)
            {
                fprintf(stderr, "[LINE %d][ERR]: Registradores RF1 E RF2 definidos de forma incorreta!", lineRead);
                continue;
            }

            // continue;
        }

        else if (instructionParsed.type == TYPE_J) // Instrução TIPO J
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
            // continue;
        }

        else if (instructionParsed.type == TYPE_B) // Instrução TIPO B
        {
            char *r1 = strtok(NULL, ",");
            char *r2 = strtok(NULL, ",");
            char *memAddress = strtok(NULL, ",");

            if (!r1)
            {
                fprintf(stderr, "[LINE %d][ERR]: Registrador r1 não especificado corretamentte.\n", lineRead);
                continue;
            }

            if (!r2)
            {
                fprintf(stderr, "[LINE %d][ERR]: Registrador r2 não especificado corretamente.\n", lineRead);
                continue;
            }

            if (!memAddress)
            {
                fprintf(stderr, "[LINE %d][ERR]: Endereço de memória não válido.\n", lineRead);
                continue;
            }

            sanitize_buffer(r1);
            sanitize_buffer(r2);
            sanitize_buffer(memAddress);
            to_lower(r1);
            to_lower(r2);

            if (!is_number(memAddress))
            {
                fprintf(stderr, "[LINE %d][ERR]: Endereço de memória não é um número!\n", lineRead);
                continue;
            }

            if (getRegByLabel(r1) == -1 || getRegByLabel(r2) == -1)
            {
                fprintf(stderr, "[LINE %d][ERR]: Registradores não válidos!\n", lineRead);
                continue;
            }

            int mem_address_int = atoi(memAddress);

            if (!mem_address_int < 0 || !mem_address_int > 15)
            {
                fprintf(stderr, "[LINE %d][ERR]: A região de memória válida vai de [0-15]!\n", lineRead);
                continue;
            }

            print_debug_typeB(instruction, lineRead, r1, r2, mem_address_int);
            // continue;
        }

        char *sobrou = strtok(NULL, " \n");

        if (sobrou != NULL)
        {
            fprintf(stderr, "[LINE %d][ERR]: Apenas uma instrução e seus argumentos devem estar por linha. Texto extra encontrado: '%s'\n", lineRead, sobrou);
        }
    }
    puts("assembler-msg:parsed.");
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