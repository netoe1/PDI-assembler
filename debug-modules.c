#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug-modules.h"

void printdiv(const char *c, int times_side, const char *message)
{
    if (!c || strlen(c) != 1 || !message || times_side <= 0)
    {
        fprintf(stderr, "[print-div][err]: Invalid parameters.\n");
        exit(EXIT_FAILURE);
    }

    printf("\n");

    for (int i = 0; i < times_side; i++)
        putchar(c[0]);

    printf(" %s ", message);

    for (int i = 0; i < times_side; i++)
        putchar(c[0]);
}
void print_debug_typeR(char *inst, int line, char *rd, char *rf1, char *rf2)
{
    if (ALLOW_DEBUG_MSG)
    {
        if (!inst || !rd || !rf1 || !rf2 || rd[0] == '\0' || rf1[0] == '\0' || rf2[0] == '\0')
        {
            puts("[PRINT-DEBUG-TYPE-R]: Invalid parameters.");
            exit(EXIT_FAILURE);
        }

        printdiv("=", 16, "PDI-TYPE-R-DEBUG");
        printf("\nLine:    [%d]", line);
        printf("\nInst:    [%s]", inst);
        printf("\nRD:      [%s]", rd);
        printf("\nRF1:     [%s]", rf1);
        printf("\nRF2      [%s]", rf2);
        printf("\n");
        printdiv("=", 16, "END");
    }
}
void print_debug_typeJ(char *inst, int line, int mem_address)
{
    if (ALLOW_DEBUG_MSG)
    {
        if (!inst || !mem_address || inst[0] == '\0')
        {
            puts("[PRINT-DEBUG-TYPE-J]: Invalid parameters.");
            exit(EXIT_FAILURE);
        }

        printdiv("=", 16, "PDI-TYPE-J-DEBUG");
        printf("\nLine:       [%d]", line);
        printf("\nInst:       [%s]", inst);
        printf("\nMemAddress: [%d]", mem_address);
        printdiv("=", 16, "END");
        printf("\n");
    }
}
void print_debug_typeI(char *inst, int line, char *rd, int imed)
{

    if (ALLOW_DEBUG_MSG)
    {
        if (!inst || !rd || !imed || inst[0] == '\0' || rd[0] == '\0')
        {
            puts("[PRINT-DEBUG-TYPE-I]: Invalid parameters.");
            exit(EXIT_FAILURE);
        }

        printdiv("=", 16, "PDI-TYPE-I-DEBUG");
        printf("\nLine:    [%d]", line);
        printf("\nInst:    [%s]", inst);
        printf("\nRD:      [%s]", rd);
        printf("\nImed:    [%d]", imed);
        printdiv("=", 16, "END");
        printf("\n");
    }
}
void print_debug_typeB(char *inst, int line, char *r1, char *r2, int mem_address)
{
    if (ALLOW_DEBUG_MSG)
    {
        if (!inst || !r1 || !r2 || r1[0] == '\0' || r2[0] == '\0')
        {
            puts("[PRINT-DEBUG-TYPE-B]: Invalid parameters.");
            exit(EXIT_FAILURE);
        }

        printdiv("=", 16, "PDI-TYPE-I-DEBUG");
        printf("\nLine:       [%d]", line);
        printf("\nInst:       [%s]", inst);
        printf("\nR1:         [%s]", r1);
        printf("\nR2:         [%s]", r2);
        printf("\nMemAddress: [%d]", mem_address);
        printdiv("=", 16, "END");
        printf("\n");
    }
}
void print_slash(char *str)
{
    if (ALLOW_DEBUG_MSG)
    {
        int i = 0;
        while (1)
        {
            if (str[i] == '\0')
            {
                printf("\\0");
                break;
            }
            printf("%c", str[i]);
            i++;
        }
    }
}