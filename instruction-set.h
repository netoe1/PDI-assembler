#ifndef INSTRUCTION_SET_H
#define INSTRUCTION_SET_H
#include "bit-impl.h"
#include "map.h"

#define R_SUB_LABEL "sub"
#define R_MUL_LABEL "mul"
#define R_SUM_LABEL "sum"
#define I_LDA_LABEL "lda"
#define I_STA_LABEL "sta"
#define J_JMP_LABEL "jmp"
#define B_BNE_LABEL "bne"
#define B_BEQ_LABEL "beq"

#define OP_LDA_CODE "000"
#define OP_SUM_CODE "001"
#define OP_SUB_CODE "010"
#define OP_MUL_CODE "011"
#define OP_JMP_CODE "100"
#define OP_BNE_CODE "101"
#define OP_BEQ_CODE "110"
#define OP_STA_CODE "111"

#define R0_LABEL "r0"
#define R1_LABEL "r1"
#define R2_LABEL "r2"
#define R3_LABEL "r3"
#define R4_LABEL "r4"
#define R5_LABEL "r5"
#define R6_LABEL "r6"
#define R7_LABEL "r7"

#define R0_CODE "000"
#define R1_CODE "001"
#define R2_CODE "010"
#define R3_CODE "011"
#define R4_CODE "100"
#define R5_CODE "101"
#define R6_CODE "110"
#define R7_CODE "111"

#define MAX_REG 8
#define MAX_INSTRUCTIONS 8
#define MAX_INSTRUCTION_LABEL_SIZE 3
#define MAX_INSTRUCTION_CODE_SIZE 3
#define MAX_REG_LABEL_SIZE 2
#define MAX_REG_CODE_SIZE 3
#define MAX_IMED_TYPE_I_SIZE 15
#define MAX_ADDRESS_SIZE 15
#define MAX_PROGRAM_MEM_SIZE 15
#define MAX_PROGRAM_STA_SIZE 15

#define SUCCESSFUL_OPERATION 0
#define FAILURE_OPERATION -1
// Instruct-Set-TypeR => TOKEN_PARSE

// New Feature IGNORE AT ALL!

typedef struct
{
    char op[MAX_INSTRUCTION_LABEL_SIZE];
    char rd[MAX_REG_LABEL_SIZE];
    char rf1[MAX_REG_LABEL_SIZE];
    char rf2[MAX_REG_LABEL_SIZE];

} InstructToken_TypeR;

// Instruct-Set-TypeI => TOKEN_PARSE

typedef struct
{
    char op[MAX_INSTRUCTION_LABEL_SIZE];
    char rd[MAX_REG_CODE_SIZE];
    int imed;
} InstructToken_TypeI;

// Instruct-Set-TypeJ => TOKEN_PARSE
typedef struct
{
    char op[MAX_INSTRUCTION_LABEL_SIZE];
    int end;
} InstructToken_TypeJ;

// Instruct-Set-TypeJ => TOKEN_PARSE
typedef struct
{
    char op[MAX_INSTRUCTION_LABEL_SIZE];
    char reg1[MAX_INSTRUCTION_LABEL_SIZE];
    char reg2[MAX_INSTRUCTION_LABEL_SIZE];

} Instruct_Token_TypeB;

typedef struct
{
    Bit opcode[4];
    Bit rd[4];
    Bit rf1[4];
    Bit rf2[4];
    Bit imed[5];
} BitStruct_R;

typedef struct
{
    Bit opcode[4];
    Bit rd[4];
    Bit imed[5];
    Bit empty[7];
} BitStruct_I;

typedef struct
{
    Bit opcode[3];
    Bit rd[3];
    Bit imed[4];
    Bit empty[6];
} BitStruct_J;

typedef struct
{
    Bit opcode[3];
    Bit reg1[3];
    Bit reg2[3];
    Bit empty[7];
} BitStruct_B;

extern const InstructionMap VALID_INSTRUCTIONS[8];
extern const RegMap VALID_REGISTERS[8];
extern const InstructionMap TYPE_R_INSTR[8];

int getRegByLabel(char label[3]); // Search if label's statement is correct.
int getRegByCode(char code[4]);   // Search if code's statement is correct.
int getInstructionByLabel(char label[4]);
int getInstructionByCode(char code[4]);
InstructionMap getInstructionStructData(char *instruction_treated);
RegMap getRegStructData(char *reg_treated);
#endif