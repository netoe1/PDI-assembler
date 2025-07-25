#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "instruction-set.h"
#include "debug-modules.h"
#include "utils.h"

const InstructionMap VALID_INSTRUCTIONS[] = {
    {I_LDA_LABEL, OP_LDA_CODE, TYPE_I}, // LDA
    {R_SUM_LABEL, OP_SUM_CODE, TYPE_R}, // SUM
    {R_SUB_LABEL, OP_SUB_CODE, TYPE_R}, // SUB
    {R_MUL_LABEL, OP_MUL_CODE, TYPE_R}, // MUL
    {J_JMP_LABEL, OP_JMP_CODE, TYPE_J}, // JMP
    {B_BNE_LABEL, OP_BNE_CODE, TYPE_B}, // BNE
    {B_BEQ_LABEL, OP_BEQ_CODE, TYPE_B}, // BEQ
    {I_STA_LABEL, OP_STA_CODE, TYPE_I}};

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

const AddressMap VALID_ADDRESS[] = {
    {MEM_ADDRESS_0_DECIMAL, MEM_ADDRESS_0_BIN},
    {MEM_ADDRESS_1_DECIMAL, MEM_ADDRESS_1_BIN},
    {MEM_ADDRESS_2_DECIMAL, MEM_ADDRESS_2_BIN},
    {MEM_ADDRESS_3_DECIMAL, MEM_ADDRESS_3_BIN},
    {MEM_ADDRESS_4_DECIMAL, MEM_ADDRESS_4_BIN},
    {MEM_ADDRESS_5_DECIMAL, MEM_ADDRESS_5_BIN},
    {MEM_ADDRESS_6_DECIMAL, MEM_ADDRESS_6_BIN},
    {MEM_ADDRESS_7_DECIMAL, MEM_ADDRESS_7_BIN},
    {MEM_ADDRESS_8_DECIMAL, MEM_ADDRESS_8_BIN},
    {MEM_ADDRESS_9_DECIMAL, MEM_ADDRESS_9_BIN},
    {MEM_ADDRESS_10_DECIMAL, MEM_ADDRESS_10_BIN},
    {MEM_ADDRESS_11_DECIMAL, MEM_ADDRESS_11_BIN},
    {MEM_ADDRESS_12_DECIMAL, MEM_ADDRESS_12_BIN},
    {MEM_ADDRESS_13_DECIMAL, MEM_ADDRESS_13_BIN},
    {MEM_ADDRESS_14_DECIMAL, MEM_ADDRESS_14_BIN},
    {MEM_ADDRESS_15_DECIMAL, MEM_ADDRESS_15_BIN},
};

const ImmediateMap VALID_IMMEDIATE[] = {
    {IMMEDIATE_0_DECIMAL, IMMEDIATE_0_BIN},
    {IMMEDIATE_1_DECIMAL, IMMEDIATE_1_BIN},
    {IMMEDIATE_2_DECIMAL, IMMEDIATE_2_BIN},
    {IMMEDIATE_3_DECIMAL, IMMEDIATE_3_BIN},
    {IMMEDIATE_4_DECIMAL, IMMEDIATE_4_BIN},
    {IMMEDIATE_5_DECIMAL, IMMEDIATE_5_BIN},
    {IMMEDIATE_6_DECIMAL, IMMEDIATE_6_BIN},
    {IMMEDIATE_7_DECIMAL, IMMEDIATE_7_BIN},
    {IMMEDIATE_8_DECIMAL, IMMEDIATE_8_BIN},
    {IMMEDIATE_9_DECIMAL, IMMEDIATE_9_BIN},
    {IMMEDIATE_10_DECIMAL, IMMEDIATE_10_BIN},
    {IMMEDIATE_11_DECIMAL, IMMEDIATE_11_BIN},
    {IMMEDIATE_12_DECIMAL, IMMEDIATE_12_BIN},
    {IMMEDIATE_13_DECIMAL, IMMEDIATE_13_BIN},
    {IMMEDIATE_14_DECIMAL, IMMEDIATE_14_BIN},
    {IMMEDIATE_15_DECIMAL, IMMEDIATE_15_BIN},
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

static InstructionMap invalidInstruction()
{
    InstructionMap invalid = {"null", "-1", -1};
    return invalid;
}

static RegMap invalidRegister()
{
    RegMap invalid = {"-1", "-1"};
    return invalid;
}

static AddressMap invalidAddress()
{
    AddressMap invalid = {"-1", "-1"};
    return invalid;
}

static ImmediateMap invalidImmediate()
{
    ImmediateMap invalid = {"-1", "-1"};
    return invalid;
}

InstructionMap getInstructionStructData(char *instruction_treated)
{
    if (!instruction_treated)
    {
        puts("instruction-set.c:getInstructionStructData(): Invalid pointer == NULL");
        exit(-1);
    }
    to_lower(instruction_treated);

    for (int i = 0; i < sizeof(VALID_INSTRUCTIONS) / sizeof(InstructionMap); i++)
    {
        if (strcmp(instruction_treated, VALID_INSTRUCTIONS[i].label) == SUCCESSFUL_OPERATION)
        {
            return VALID_INSTRUCTIONS[i];
        }
    }
    return invalidInstruction();
}

RegMap getRegStructData(char *reg_treated)
{
    if (!reg_treated)
    {
        puts("instruction-set.c:getRegStructData(): Invalid pointer == NULL");
        exit(-1);
    }

    to_lower(reg_treated);

    for (int i = 0; i < sizeof(VALID_REGISTERS) / sizeof(RegMap); i++)
    {
        if (strcmp(reg_treated, VALID_REGISTERS[i].label) == SUCCESSFUL_OPERATION)
        {
            return VALID_REGISTERS[i];
        }
    }
    return invalidRegister();
}

AddressMap getAddressStructData(const char *address)
{
    if (!address)
    {
        puts("instruction-set.c:getAddressStructData(): Invalid pointer == NULL");
        exit(-1);
    }

    for (int i = 0; i < MAX_ADDRESS_SIZE; i++)
    {
        if (strcmp(address, VALID_ADDRESS[i].address) == 0)
        {
            return VALID_ADDRESS[i];
        }
    }

    return invalidAddress();
}

ImmediateMap getImmediateStructData(const char *immediate)
{
    if (!immediate)
    {
        puts("instruction-set.c:getImmediateStructData(): Invalid pointer == NULL");
        exit(-1);
    }

    for (int i = 0; i < MAX_ADDRESS_SIZE; i++)
    {
        if (strcmp(immediate, VALID_IMMEDIATE[i].value) == 0)
        {
            return VALID_IMMEDIATE[i];
        }
    }
    return invalidImmediate();
}

#pragma region PRINT

void printInstr_typej(InstructToken_TypeJ instr)
{
    printdiv("=", 16, "Instruction TYPE-J");
    printf("Opcode:%s\n", instr.op);
    printf("Endereço:%d\n", instr.end);
    printf("\n");
}
void printInstr_typeb(InstructToken_TypeB instr)
{
    printdiv("=", 16, "Instruction TYPE-B");
    printf("Opcode:%s\n", instr.op);
    printf("Reg1:%s\n", instr.reg1);
    printf("Reg2:%s\n", instr.reg2);
    printf("\n");
}
void printInstr_typei(InstructToken_TypeI instr)
{
    printdiv("=", 16, "Instruction TYPE-I");
    printf("Opcode:%s\n", instr.op);
    printf("Reg1:%s\n", instr.rd);
    printf("Imediato:%d\n", instr.imed);
    printf("\n");
}
void printInstr_typer(InstructToken_TypeR instr)
{
    printdiv("=", 16, "Instruction TYPE-R");
    printf("Opcode:%s\n", instr.op);
    printf("Reg Destino:%s\n", instr.rd);
    printf("Reg Fonte 1:%s\n", instr.rf1);
    printf("Reg Fonte 2:%s\n", instr.rf2);
    printf("\n");
}
#pragma endregion PRINT