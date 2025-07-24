#include "coder.h"
#include "instruction-set.h"
#include "map.h"
#include <stdlib.h>
#include <memory.h>
#include <string.h>

static void convertIntegerToBin16(int integer, char res[], int n) // Convert a integer number to a binary string 16 bits
{
    // Inicializa o array de resultado com zeros
    for (int i = 0; i < n; i++)
    {
        res[i] = '0';
    }
    res[n] = '\0'; // Adiciona terminador de string

    // Trata números negativos (complemento de 2)
    if (integer < 0)
    {
        // Converte para positivo e depois aplica complemento de 2
        integer = -integer;

        // Converte o valor absoluto para binário
        for (int i = n - 1; i >= 0 && integer > 0; i--)
        {
            res[i] = (integer % 2) + '0';
            integer /= 2;
        }

        // Aplica complemento de 1 (inverte todos os bits)
        for (int i = 0; i < n; i++)
        {
            res[i] = (res[i] == '0') ? '1' : '0';
        }

        // Aplica complemento de 2 (adiciona 1)
        int carry = 1;
        for (int i = n - 1; i >= 0 && carry; i--)
        {
            if (res[i] == '0')
            {
                res[i] = '1';
                carry = 0;
            }
            else
            {
                res[i] = '0';
            }
        }
    }
    else
    {
        // Para números positivos, conversão direta
        for (int i = n - 1; i >= 0 && integer > 0; i--)
        {
            res[i] = (integer % 2) + '0';
            integer /= 2;
        }
    }
}

InstructToken_TypeJ parseToCoder_typej(const char *instr_treated, const char *imed_treated)
{
    InstructToken_TypeJ send = {instr_treated, imed_treated};
    return send;
}
InstructToken_TypeI parseToCoder_typei(const char *instr_treated, const char *rd_treated, const char *imed_treated)
{
    InstructToken_TypeI typei = {instr_treated, rd_treated, imed_treated};
    return typei;
}
InstructToken_TypeB parseToCoder_typeb(const char *instr_treated, const char *r1_treated, const char *r2_treated, const char *address_treated)
{
    InstructToken_TypeB typeb = {instr_treated, r1_treated, r2_treated, address_treated};
    return typeb;
}
InstructToken_TypeR parseToDCoder_typer(const char *instr_treated, const char *rd_treated, const char *rf1_treated, const char *rf2_treated)
{
    InstructToken_TypeR typer = {instr_treated, rd_treated, rf1_treated, rf2_treated};
    return typer;
}

BitStruct_J coderToBit_typej(InstructToken_TypeJ instruction_struct);
BitStruct_I coderToBit_typei(InstructToken_TypeI instruction_struct);
BitStruct_B coderToBit_typeb(InstructToken_TypeB instruction_struct);
BitStruct_R coderToBit_typer(InstructToken_TypeR instruction_struct);

void bitTostr_typej(BitStruct_J bit_struct, char instruction[MAX_BITS_INSTRUCTION + 1]);
void bitToStr_typei(BitStruct_I bit_struct, char instruction[MAX_BITS_INSTRUCTION + 1]);
void bitToStr_typeb(BitStruct_B bit_struct, char instruction[MAX_BITS_INSTRUCTION + 1]);
void bitToStr_typer(BitStruct_R bit_struct, char instruction[MAX_BITS_INSTRUCTION + 1]);
