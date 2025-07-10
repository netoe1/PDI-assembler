#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>
#include <stdbool.h>
#include "instruction-set.h"
#include "utils.h"

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
    char *instr, *reg, *valStr;
    int val;
    int lineRead = 0;
    while (fgets(line, sizeof(line), openedFile) != NULL)
    {
        if (line[0] == '\n' || line[0] == '#')
        {
            // puts("[forg-info]: Você passou por um comentário!");
            continue;
        }

        if (line[0] == '\n')
        {
            // puts("[forg-info]: Você passou por um final de linha!");
            continue;
        }

        instr = strtok(line, " "); // Separa em tokens
        to_lower(instr);
        if (!instr)
        {
            fprintf(stderr, "[forg-mount]: Erro ao dar parse na instrução!\n");
            return;
        }

        if (strlen(instr) != MAX_INSTRUCTION_LABEL_SIZE)
        {
            fprintf(stderr, "[forg-mount]: Instrução com  tamanho inválido, as labels devem conter apenas 3 letras!\n");
        }

        int instrn = searchInstructionByLabel(instr); // Verifica se a opção existe no map
        if (instrn == FAILURE_OPERATION)
        {
            fprintf(stderr, "[forg-mount]: A instrução \'%s\' não existe na arquitetura.\n", instr);
            return;
        }

        reg = strtok(NULL, ",");

        if (!reg)
        {
            fprintf(stderr, "[forg-mount]: Erro ao dar parse no registrador!\n");
            return;
        }

        if (strlen(reg) != MAX_REG_LABEL_SIZE)
        {
            fprintf(stderr, "[forg-mount]: Instrução com tamanho inválido, as labels devem conter apenas 2 letras!\n");
        }

        int regn = searchRegByCode(reg);
        if (regn == FAILURE_OPERATION)
        {
            fprintf(stderr, "[forg-mount]: O Registrador \'%s\' não existe na arquitetura.\n", reg);
            return;
        }

        char *nbuf = strtok(NULL, "");
        if (!nbuf)
        {
            fprintf(stderr, "[forg-mount]: Erro ao dar parse no imediato\n");
            return;
        }

        val = is_number(nbuf);
        if (!val)
        {
            fprintf(stderr, "[forg-mount]: O valor que você digitou não é um número!\n");
            return;
        }

        if (val < 0 || val > MAX_IMED_TYPE_I_SIZE)
        {
            fprintf(stderr, "[forg-mount]: O endereço de memória que você digitou não é válido.!\n");
            return;
        }
        lineRead++;
    }

    printf("Instrução: %s\n", instr);
    printf("Registrador %s\n", reg);
    printf("Imed %d\n", val);
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