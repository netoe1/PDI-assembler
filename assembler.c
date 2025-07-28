#include "assembler.h"
#include "utils.h"
#include "instruction-set.h"
#define LINE_LIMIT 256

char currentFile[30];

FILE *
readFile(const char *filename)
{

    if (!filename)
    {
        fprintf(stderr, "assembler.c: readfile(): Invalid pointer to read.");
        exit(-1);
    }

    FILE *f = fopen(filename, "r");
    if (!f)
    {
        fprintf(stderr, "assembler.c: readfile(): No permission to read || the file's doesn't exist.");
        exit(-1);
    }
    strncpy(currentFile, filename, sizeof(currentFile) - 1);
    return f;
}
void parseFile(FILE *openedFile)
{
    char line[LINE_LIMIT];
    char parsedLine[LINE_LIMIT];
    char *instruction = NULL;
    char *reg = NULL;
    char *valStr = NULL;
    int val;
    int lineRead = 0;

    while (fgets(line, sizeof(line), openedFile) != NULL)
    {
        lower_str(parsedLine, line, LINE_LIMIT - 1);
        lineRead++;
        if (parsedLine[0] == '\n' || parsedLine[0] == '#' || is_line_empty(parsedLine))
        {
            continue;
        }

        instruction = strtok(parsedLine, " ");

        if (!instruction) // Verifica se o strtok() foi concluído com sucesso
        {
            fprintf(stderr, "ERR-%s:l.%d: Instrução inválida: %s.\n", currentFile, lineRead, instruction);
            continue;
        }
        sanitize_buffer(instruction);
        InstructionMap instructionParsed = getInstructionStructData(instruction);

        if (strcmp(instructionParsed.code, "-1") == 0)
        {
            fprintf(stderr, "ERR-%s:l.%d: A instrução %s não existe na arquitetura.\n", currentFile, lineRead, instruction);
            continue;
        }

        if (instructionParsed.type == TYPE_I)
        {

            reg = strtok(NULL, ",");

            if (!reg || strlen(reg) == 0)
            {

                fprintf(stderr, "ERR%s:l.%d:Faltando registrador na instrução %s.\n", currentFile, lineRead, instruction);
                continue;
            }
            sanitize_buffer(reg);
            int regn = getRegByLabel(reg);
            if (regn == FAILURE_OPERATION)
            {
                fprintf(stderr, "ERR-%s:l.%d: Registrador %s não existe.\n", currentFile, lineRead, reg);
                continue;
            }

            valStr = strtok(NULL, ",");
            sanitize_buffer(valStr);

            if (!valStr || strlen(valStr) == 0)
            {
                fprintf(stderr, "ERR-%s:l.%d: Valor imediato ausente após registrador '%s'.\n", currentFile, lineRead, reg);
                continue;
            }

            if (!is_number(valStr))
            {
                fprintf(stderr, "ERR-%s:l.%d: Valor %s não é um número válido.\n", currentFile, lineRead, valStr);
                continue;
            }

            val = atoi(valStr);
            if (val < 0 || val > MAX_IMED_TYPE_I_SIZE)
            {
                fprintf(stderr, "ERR-%s:l.%d: Valor imediato fora do intervalo permitido: %d\n", currentFile, lineRead, val);
                continue;
            }
            // print_debug_typeI(instruction, lineRead, reg, val);
        }

        else if (instructionParsed.type == TYPE_R) // Instrução TIPO R
        {
            char *rd = strtok(NULL, ",");
            if (!rd)
            {
                fprintf(stderr, "ERR-%s:l.%d: Registrador destino não definido\n", currentFile, lineRead);
                continue;
            }

            char *rf1 = strtok(NULL, ",");
            if (!rf1)
            {
                fprintf(stderr, "ERR-%s:l.%d: Registrador fonte 1 não definido:\n", currentFile, lineRead);
                continue;
            }

            char *rf2 = strtok(NULL, ",");
            if (!rf2)
            {
                fprintf(stderr, "ERR-%s:l.%d: Registrador fonte 2 não definido\n", currentFile, lineRead);
                continue;
            }

            sanitize_buffer(rd);
            sanitize_buffer(rf1);
            sanitize_buffer(rf2);
            // print_debug_typeR(instruction, lineRead, rd, rf1, rf2);

            if (getRegByLabel(rf1) == -1 || getRegByLabel(rf2) == -1)
            {
                fprintf(stderr, "ERR-%s:l.%d: Registradores RF1 E RF2 definidos de forma incorreta!\n", currentFile, lineRead);
                continue;
            }
        }

        else if (instructionParsed.type == TYPE_J) // Instrução TIPO J
        {
            char *mem_address = strtok(NULL, "\n");
            if (!is_number(mem_address))
            {
                fprintf(stderr, "ERR-%s:l.%d: Valor '%s' não é um endereço de memória válido.\n", currentFile, lineRead, mem_address);
                continue;
            }

            int mem_address_int = atoi(mem_address);
            if (mem_address_int < 0 || mem_address_int > MAX_PROGRAM_MEM_SIZE)
            {
                fprintf(stderr, "ERR-%s:l.%d: O valor está fora do limite para a memória de programa.\n", currentFile, lineRead);
                continue;
            }

            // print_debug_typeJ(instruction, lineRead, mem_address_int);
        }

        else if (instructionParsed.type == TYPE_B) // Instrução TIPO B
        {
            char *r1 = strtok(NULL, ",");
            char *r2 = strtok(NULL, ",");
            char *memAddress = strtok(NULL, ",");

            if (!r1)
            {
                fprintf(stderr, "ERR-%s:l.%d:\nRegistrador r1 não especificado corretamentte.\n", currentFile, lineRead);
                continue;
            }

            if (!r2)
            {
                fprintf(stderr, "ERR-%s:l.%d:\nRegistrador r2 não especificado corretamente.\n", currentFile, lineRead);
                continue;
            }

            if (!memAddress)
            {
                fprintf(stderr, "ERR-%s:l.%d:\nEndereço de memória não válido.\n", currentFile, lineRead);
                continue;
            }

            sanitize_buffer(r1);
            sanitize_buffer(r2);
            sanitize_buffer(memAddress);

            if (!is_number(memAddress))
            {
                fprintf(stderr, "ERR-%s:l.%d:\nEndereço de memória não é um número!\n", currentFile, lineRead);
                continue;
            }

            if (getRegByLabel(r1) == -1 || getRegByLabel(r2) == -1)
            {
                fprintf(stderr, "ERR-%s:l.%d:\nRegistradores não válidos!\n", currentFile, lineRead);
                continue;
            }

            int mem_address_int = atoi(memAddress);

            if (mem_address_int < 0 || mem_address_int > 15)
            {
                fprintf(stderr, "ERR-%s:l.%d:\nA região de memória válida vai de [0-15]!\n", currentFile, lineRead);
                continue;
            }

            // print_debug_typeB(instruction, lineRead, r1, r2, mem_address_int);
        }

        char *sobrou = strtok(NULL, " \n");

        if (sobrou != NULL)
        {
            fprintf(stderr, "ERR-%s:l.%d:\nApenas uma instrução e seus argumentos devem estar por linha.\n", currentFile, lineRead);
        }
    }
    puts("assembler-info: ending-parse...");
}
void closeFile(FILE *closeFile)
{
    if (!closeFile)
    {
        perror("assembler.c: closeFile(): Invalid pointer to file.");
        exit(-1);
    }

    if (fclose(closeFile) != 0)
    {
        perror("assembler.c: closeFile(): Error while closing a file.");
        exit(-1);
    }
}

int main(void)
{
    setlocale(LC_ALL, "");
    FILE *f = readFile("teste.asm");
    FILE *output;

    parseFile(f);
    closeFile(f);
}
