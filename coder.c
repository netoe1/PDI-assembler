#include "coder.h"
#include "instruction-set.h"
#include "map.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

// static void convertIntegerToBin(int integer, char res[], int n)
// {
//     for (int i = 0; i < n; i++)
//         res[i] = '0';
//     res[n] = '\0';

//     if (integer < 0)
//     {
//         integer = -integer;
//         for (int i = n - 1; i >= 0 && integer > 0; i--)
//         {
//             res[i] = (integer % 2) + '0';
//             integer /= 2;
//         }
//         for (int i = 0; i < n; i++)
//             res[i] = (res[i] == '0') ? '1' : '0';

//         int carry = 1;
//         for (int i = n - 1; i >= 0 && carry; i--)
//         {
//             if (res[i] == '0')
//             {
//                 res[i] = '1';
//                 carry = 0;
//             }
//             else
//                 res[i] = '0';
//         }
//     }
//     else
//     {
//         for (int i = n - 1; i >= 0 && integer > 0; i--)
//         {
//             res[i] = (integer % 2) + '0';
//             integer /= 2;
//         }
//     }
// }

static void settingOpcode(const char opcode[4], char output[17])
{
    memcpy(output, opcode, 3);
}

void codeinstruction_typeJ(const char *instruction_treated, const char *address_treated, char output[MAX_BITS_INSTRUCTION + 1])
{
    if (!instruction_treated || !address_treated || !output)
    {
        fprintf(stderr, "Erro: parâmetro nulo em codeinstruction_typeJ.\n");
        return;
    }

    memset(output, '0', MAX_BITS_INSTRUCTION);
    output[MAX_BITS_INSTRUCTION] = '\0';

    // Define o opcode fixo "100" nos bits 0–2
    settingOpcode(OP_JMP_CODE, output);

    AddressMap address = getAddressStructData(address_treated);

    if (strlen(address.code) != 4)
    {
        // bits 3–6
        fprintf(stderr, "Erro: Código de endereço inválido em codeinstruction_typeJ.\n");
        return;
    }
    memcpy(&output[3], address.code, 4);
}

void codeinstruction_typeI(const char *instruction_treated, const char *rd_treated, const char *imed_treated, char output[MAX_BITS_INSTRUCTION + 1])
{
    if (!instruction_treated || !rd_treated || !imed_treated || !output)
    {
        fprintf(stderr, "Erro: parâmetro nulo em codeinstruction_typeI.\n");
        return;
    }

    memset(output, '0', MAX_BITS_INSTRUCTION);
    output[MAX_BITS_INSTRUCTION] = '\0';

    // bits 0–2: opcode
    InstructionMap instr_struct = getInstructionStructData(instruction_treated);

    if (!strcmp(instr_struct.code, "-1") == 0)
    {
        fprintf(stderr, "Erro: instrução inválida em getInstructionStructData\n");
        return;
    }

    if (strcmp(instr_struct.label, I_LDA_LABEL) == 0)
    {
        settingOpcode(OP_LDA_CODE, output);
    }
    else if (strcmp(instr_struct.label, I_STA_LABEL) == 0)
    {
        settingOpcode(OP_STA_CODE, output);
    }

    // bits 4–6: registrador destino
    RegMap rd_struct = getRegStructData(rd_treated);
    if (strlen(rd_struct.code) != 3)
    {
        fprintf(stderr, "Erro: Registrador destino com tamanho inválido em codeInstruction_typeI.\n");
        return;
    }

    memcpy(&output[4], rd_struct.code, 3);

    // bits 8–11: imediato
    ImmediateMap imed_struct = getImmediateStructData(imed_treated);
    if (strlen(imed_struct.code) != 4)
    {
        fprintf(stderr, "Erro: Imediato com tamanho inválido em codeInstruction_typeI.\n");
        return;
    }

    memcpy(&output[8], imed_struct.code, 4);
}

void codeinstruction_typeB(const char *instruction_treated, const char *r1, const char *r2, const char *address, char output[MAX_BITS_INSTRUCTION + 1])
{
    memset(output, '0', MAX_BITS_INSTRUCTION);
    output[MAX_BITS_INSTRUCTION] = '\0';

    if (!instruction_treated)
    {
        fprintf(stderr, "Erro: instrução inválida nos parametros de codeinstruction_typeB.\n");
        return;
    }

    if (!r1)
    {
        fprintf(stderr, "Erro: r1 inválido nos parametros de codeinstruction_typeB.\n");
        return;
    }

    if (!r2)
    {
        fprintf(stderr, "Erro: r2 inválido nos parametros de codeinstruction_typeB.\n");
        return;
    }

    if (!address)
    {
        fprintf(stderr, "Erro: address inválido nos parametros de codeinstruction_typeB.\n");
        return;
    }

    if (!output)
    {
        fprintf(stderr, "Erro: output inválido nos parametros de codeinstruction_typeB.\n");
        return;
    }

    if (strcmp(B_BNE_LABEL, instruction_treated) == 0)
    {
        settingOpcode(OP_BNE_CODE, output);
    }
    else if (strcmp(B_BEQ_LABEL, instruction_treated) == 0)
    {
        settingOpcode(OP_BEQ_CODE, output);
    }
    else
    {
        fprintf(stderr, "Erro: instrução inválida para typeB.\n");
        return;
    }

    InstructionMap instr_struct = getInstructionStructData(instruction_treated);
    RegMap r1_struct = getRegStructData(r1);
    RegMap r2_struct = getRegStructData(r2);
    AddressMap address_struct = getAddressStructData(address);

    if (strcmp(instr_struct.code, "-1") == 0)
    {
        fprintf(stderr, "Erro: instrução inválida em codeinstruction_typeB.\n");
        return;
    }

    if (strcmp(r1_struct.code, "-1") == 0)
    {
        fprintf(stderr, "Erro: r1 inválido em codeinstruction_typeB.\n");
        return;
    }

    if (strcmp(r2_struct.code, "-1") == 0)
    {
        fprintf(stderr, "Erro: r2 inválido em codeinstruction_typeB.\n");
        return;
    }

    if (strcmp(address_struct.code, "-1") == 0)
    {
        fprintf(stderr, "Erro: address inválido em codeinstruction_typeB.\n");
        return;
    }

    memcpy(&output[3], r1_struct.code, 3);
    memcpy(&output[7], r2_struct.code, 3);
    memcpy(&output[11], r2_struct.code, 3);
}

void codeinstruction_typeR(const char *instruction_treated, const char *rd, const char *rf1, const char *rf2, char output[MAX_BITS_INSTRUCTION + 1])
{
    memset(output, '0', MAX_BITS_INSTRUCTION);
    output[MAX_BITS_INSTRUCTION] = '\0';
}
