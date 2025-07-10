#include "instruction-set.h"
#include "utils.h"
#include <string.h>
#include <ctype.h>

const InstructionMap VALID_INSTRUCTIONS[] = {
    {I_LDA_LABEL, OP_LDA_CODE}, // LDA
    {R_SUM_LABEL, OP_SUM_CODE}, // SUM
    {R_SUB_LABEL, OP_SUB_CODE}, // SUB
    {R_MUL_LABEL, OP_MUL_CODE}, // MUL
    {J_JMP_LABEL, OP_JMP_CODE}, // JMP
    {B_BNE_LABEL, OP_BNE_CODE}, // BNE
    {B_BEQ_LABEL, OP_BEQ_CODE}, // BEQ
    {I_STA_LABEL, OP_STA_CODE}, // STA
};

const RegMap VALID_REGISTERS[] = {
    {R0_LABEL, R0_CODE},
    {R1_LABEL, R1_CODE},
    {R2_LABEL, R2_CODE},
    {R3_LABEL, R3_CODE},
    {R4_LABEL, R4_CODE},
    {R5_LABEL, R5_CODE},
    {R6_LABEL, R6_LABEL},
    {R7_LABEL, R7_CODE},
};

int searchRegByLabel(char label[3])
{
    to_lower(label);
    for (int i = 0; i < 8; i++)
    {
        if (strcmp(label, VALID_REGISTERS[i].label) == SUCCESSFUL_OPERATION)
        {
            return i;
        }
    }
    return -1;
}
// Search if label's statement is correct.
int searchRegByCode(char code[4])
{

    to_lower(code);

    for (int i = 0; i < 8; i++)
    {
        if (strcmp(code, VALID_REGISTERS[i].code) == SUCCESSFUL_OPERATION)
        {
            return i;
        }
    }
    return -1;
}

int searchInstructionByLabel(char label[4])
{
    to_lower(label);

    for (int i = 0; i < 8; i++)
    {
        if (strcmp(label, VALID_INSTRUCTIONS[i].label) == SUCCESSFUL_OPERATION)
        {
            return i;
        }
    }
    return -1;
}
int searchInstructionByCode(char code[4])
{
    to_lower(code);

    for (int i = 0; i < 8; i++)
    {
        if (strcmp(code, VALID_INSTRUCTIONS[i].code) == SUCCESSFUL_OPERATION)
        {
            return i;
        }
    }
    return -1;
}
