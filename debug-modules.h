#ifndef DEBUG_MODULES_H
#define DEBUG_MODULES_H

void print_debug_typeR(char *inst, int line, char *rd, char *rf1, char *rf2);
void print_debug_typeJ(char *inst, int line, int mem_address);
void print_debug_typeI(char *inst, int line, char *rd, int imed);
void print_debug_typeB(char *inst, int line, char *r1, char *r2, int mem_address);
void printdiv(const char *c, int times_side, const char *message); // Print divisories.
void print_slash(char *str);

#endif