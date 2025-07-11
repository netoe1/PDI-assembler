#ifndef UTILS_H
#define UTILS_H
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>

bool is_number(const char *str);
void to_lower(char *str);
void print_slash(char *str);
void sanitize_buffer(char *buffer);
#endif