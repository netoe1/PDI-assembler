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

void testCoderTypeB(char *instr, char *r1, char *r2, char *address, char output[17])
{
    codeinstruction_typeB(instr, r1, r2, address, output);
    puts(output);
}

int main(void)
{
    char output[17];
    //testCoderTypeJ("jmp", "10", output);
    //testCoderTypeI("lda", "r0", "10", output);
    testCoderTypeB("beq", "r0", "r1", "10", output);

    return 0;
}