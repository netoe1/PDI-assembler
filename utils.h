#ifndef UTILS_H
#define UTILS_H
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>

bool is_number(const char *str);                                   // Function to verify if is a number.
void to_lower(char *str);                                          // To lower for strings (ANSI_C)
                                 // print with null chars
void sanitize_buffer(char *buffer);                                // Sanitize strings.

bool is_line_empty(const char *line);                              // Verifica linhas vazias
#endif