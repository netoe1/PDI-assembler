#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "debug-modules.h"

#define EXTENSION_SUPPORTED ".asmth"

FILE *readFile(const char *filename);
void parseFile(FILE *openedFile);
void closeFile(FILE *closeFile);
#endif