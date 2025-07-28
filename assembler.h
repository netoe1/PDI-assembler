#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include <stdio.h>
#include <stdlib.h>

FILE *readFile(const char *filename);
void parseFile(FILE *openedFile);
void closeFile(FILE *closeFile);
#endif