#include "coder.c"
#include <stdio.h>

void testCoderTypeJ(char *instr, char *address, char output[17])
{
    codeinstruction_typeJ(instr, address, output);
    puts(output);
}

void testCoderTypeI(char *instr, char *rd, char *imed, char output[17])
{
    codeinstruction_typeI(instr, rd, imed, output);
    puts(output);
}

int main(void)
{
    char output[17];
    // testCoderTypeJ("jmp", "10", output);

    char *instr = "sta";
    char *rd = "r2";
    char *imed = "10";
    codeinstruction_typeI(instr, rd, imed, output);
    puts(output);
    return 0;
}