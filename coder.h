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

BitStruct_J coderToBit_typej(const char *instr_treated, const char *imed_treated);
BitStruct_I coderToBit_typei(const char *instr_treated, const char *rd_treated, const char *imed_treated);
BitStruct_B coderToBit_typeb(const char *instr_treated, const char *r1_treated, const char *r2_treated, const char *address_treated);
BitStruct_R coderToBit_typer(const char *instr_treated, const char *rd_treated, const char *rf1_treated, const char *rf2_treated);

// Returns a str with bits, if you borrow struct
// Returns a str in a bit format.

// Write codeline line by line in a output file.
// If returns -1, an error ocurred.
int writecodeOnFile(const char *filePath, char *code_treated);
#endif