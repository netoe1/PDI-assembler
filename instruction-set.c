#include <string.h>
#include <ctype.h>
#include "instruction-set.h"
#include "utils.h"

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
    {R0_LABEL, R0_CODE},  // R0
    {R1_LABEL, R1_CODE},  // R1
    {R2_LABEL, R2_CODE},  // R2
    {R3_LABEL, R3_CODE},  // R3
    {R4_LABEL, R4_CODE},  // R4
    {R5_LABEL, R5_CODE},  // R5
    {R6_LABEL, R6_LABEL}, // R6
    {R7_LABEL, R7_CODE},  // R7
};

int getRegByLabel(char label[3])
{
    to_lower(label);
    for (int i = 0; i < MAX_REG; i++)
    {
        if (strcmp(label, VALID_REGISTERS[i].label) == SUCCESSFUL_OPERATION)
        {
            return i;
        }
    }
    return -1;
}
// get if label's statement is correct.
int getRegByCode(char code[4])
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

int getInstructionByLabel(char label[4])
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
int getInstructionByCode(char code[4])
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

InstructionType getInstructionType(char *instruction_treated)
{
    to_lower(instruction_treated);

    if (strcmp(I_LDA_LABEL, instruction_treated) == SUCCESSFUL_OPERATION ||
        strcmp(I_STA_LABEL, instruction_treated) == SUCCESSFUL_OPERATION)
    {
        return TYPE_I;
    }
    if (strcmp(R_MUL_LABEL, instruction_treated) == SUCCESSFUL_OPERATION ||
        strcmp(R_SUB_LABEL, instruction_treated) == SUCCESSFUL_OPERATION ||
        strcmp(R_SUM_LABEL, instruction_treated) == SUCCESSFUL_OPERATION)
    {
        return TYPE_R;
    }
    if (strcmp(J_JMP_LABEL, instruction_treated) == SUCCESSFUL_OPERATION)
    {
        return TYPE_J;
    }

    if (strcmp(B_BEQ_LABEL, instruction_treated) == SUCCESSFUL_OPERATION ||
        strcmp(B_BNE_LABEL, instruction_treated) == SUCCESSFUL_OPERATION)
    {
        return TYPE_B;
    }

    return INVALID_INSTRUCTION;
}
