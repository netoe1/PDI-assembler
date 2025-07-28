#ifndef CODER_H
#define CODER_H

#include "instruction-set.h"
#include "map.h"
#include <stdlib.h>

void codeinstruction_typeJ(const char *instruction_treated, const char *address_treated, char output[MAX_BITS_INSTRUCTION + 1]); // Tested!
void codeinstruction_typeI(const char *instruction_treated, const char *rd_treated, const char *imed_treated, char output[MAX_BITS_INSTRUCTION + 1]); // Tested!
void codeinstruction_typeB(const char *instruction_treated, const char *r1, const char *r2, const char *address, char output[MAX_BITS_INSTRUCTION + 1]);
void codeinstruction_typeR(const char *instruction_treated, const char *rd, const char *rf1, const char *rf2, char output[MAX_BITS_INSTRUCTION + 1]);

// void bitToStr_typej(BitStruct_J bit_struct, char instruction[MAX_BITS_INSTRUCTION + 1]);
// void bitToStr_typei(BitStruct_I bit_struct, char instruction[MAX_BITS_INSTRUCTION + 1]);
// void bitToStr_typeb(BitStruct_B bit_struct, char instruction[MAX_BITS_INSTRUCTION + 1]);
// void bitToStr_typer(BitStruct_R bit_struct, char instruction[MAX_BITS_INSTRUCTION + 1]);

// void bitTostr(InstructionTypes type, char instruction[MAX_BITS_INSTRUCTION + 1]); // mux with types.

#endif