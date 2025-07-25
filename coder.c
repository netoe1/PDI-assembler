#include "coder.h"
#include "instruction-set.h"
#include "map.h"
#include <stdlib.h>
#include <memory.h>
#include <string.h>

static void convertIntegerToBin(int integer, char res[], int n)
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
    RegMap rd_struct = getRegStructData(rd_treated);
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
