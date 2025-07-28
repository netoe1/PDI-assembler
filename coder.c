#include "coder.h"
#include "instruction-set.h"
#include "map.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

static void convertIntegerToBin(int integer, char res[], int n)
{
    for (int i = 0; i < n; i++)
        res[i] = '0';
    res[n] = '\0';

    if (integer < 0)
    {
        integer = -integer;
        for (int i = n - 1; i >= 0 && integer > 0; i--)
        {
            res[i] = (integer % 2) + '0';
            integer /= 2;
        }
        for (int i = 0; i < n; i++)
            res[i] = (res[i] == '0') ? '1' : '0';

        int carry = 1;
        for (int i = n - 1; i >= 0 && carry; i--)
        {
            if (res[i] == '0')
            {
                res[i] = '1';
                carry = 0;
            }
            else
                res[i] = '0';
        }
    }
    else
    {
        for (int i = n - 1; i >= 0 && integer > 0; i--)
        {
            res[i] = (integer % 2) + '0';
            integer /= 2;
        }
    }
}

void codeinstruction_typeJ(const char *instruction_treated, const char *address_treated, char output[MAX_BITS_INSTRUCTION + 1])
{
    memset(output, '0', MAX_BITS_INSTRUCTION);
    output[MAX_BITS_INSTRUCTION] = '\0';

    output[0] = '1';
    output[1] = '0';
    output[2] = '0';

    AddressMap address = getAddressStructData(address_treated);
    memcpy(&output[3], address.code, 4);
}

void codeinstruction_typeI(const char *instruction_treated, const char *rd_treated, const char *imed_treated, char output[MAX_BITS_INSTRUCTION + 1])
{
    memset(output, '0', MAX_BITS_INSTRUCTION);
    output[MAX_BITS_INSTRUCTION] = '\0';

    InstructionMap instr_struct = getInstructionStructData((char *)instruction_treated);
    // RegMap rd_struct = getRegStructData((char *)rd_treated);
}

void codeinstruction_typeB(const char *instruction_treated, const char *r1, const char *r2, const char *address, char output[MAX_BITS_INSTRUCTION + 1])
{
    memset(output, '0', MAX_BITS_INSTRUCTION);
    output[MAX_BITS_INSTRUCTION] = '\0';
}

void codeinstruction_typeR(const char *instruction_treated, const char *rd, const char *rf1, const char *rf2, char output[MAX_BITS_INSTRUCTION + 1])
{
    memset(output, '0', MAX_BITS_INSTRUCTION);
    output[MAX_BITS_INSTRUCTION] = '\0';
}
