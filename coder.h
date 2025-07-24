#ifndef CODER_H
#define CODER_H

#include "instruction-set.h"
#include "map.h"
#include <stdlib.h>

// Get all in char* and returns parsed in a struct.
InstructToken_TypeJ parseToCoder_typej(const char *instr_treated, const char *imed_treated);
InstructToken_TypeI parseToCoder_typei(const char *instr_treated, const char *rd_treated, const char *imed_treated);
InstructToken_TypeB parseToCoder_typeb(const char *instr_treated, const char *r1_treated, const char *r2_treated, const char *address_treated);
InstructToken_TypeR parseToDCoder_typer(const char *instr_treated, const char *rd_treated, const char *rf1_treated, const char *rf2_treated);

// Do the same as above, but return parsed in bit struct, defined in bit-impl.h

BitStruct_J coderToBit_typej(InstructToken_TypeJ instruction_struct);
BitStruct_I coderTobit_typei(InstructToken_TypeI instruction_struct);
BitStruct_B coderToBit_typeb(InstructToken_TypeB instruction_struct);
BitStruct_R coderToBit_typer(InstructToken_TypeR instruction_struct);

// Returns a str with bits, if you borrow struct
// Returns a str in a bit format.

void bitToStr_typej(BitStruct_J bit_struct, char instruction[MAX_BITS_INSTRUCTION + 1]);
void bitToStr_typei(BitStruct_I bit_struct, char instruction[MAX_BITS_INSTRUCTION + 1]);
void bitToStr_typeb(BitStruct_B bit_struct, char instruction[MAX_BITS_INSTRUCTION + 1]);
void bitToStr_typer(BitStruct_R bit_struct, char instruction[MAX_BITS_INSTRUCTION + 1]);

void bitTostr(InstructionTypes type, char instruction[MAX_BITS_INSTRUCTION + 1]); // mux with types.

#endif