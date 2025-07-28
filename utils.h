#ifndef UTILS_H
#define UTILS_H
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>

bool is_number(const char *str);                             // Function to verify if is a number.
void sanitize_buffer(char *buffer);                          // Sanitize strings.
bool is_line_empty(const char *line);                        // Verifica linhas vazias
void lower_str(char *dst, const char *src, size_t dst_size); // Converte uma string para minúsculas, de forma segura
                                                             // dst deve ter tamanho suficiente (igual ou maior que len(src) + 1)
char *trim(char *str);
#endif