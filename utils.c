#include "utils.h"
#include <string.h>
#include <stdlib.h>
bool is_number(const char *str)
{
    if (*str == '-' || *str == '+')
        str++;

    if (*str == '\0')
        return false;

    while (*str)
    {
        if (!isdigit((unsigned char)*str))
            return false;
        str++;
    }
    return true;
}

void to_lower(char *str)
{
    while (*str)
    {
        *str = tolower((unsigned char)*str);
        str++;
    }
}

void sanitize_buffer(char *line)
{
    char *src = line, *dst = line;
    while (*src)
    {
        if (*src != '\n' && *src != '\r')
        {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}

bool is_line_empty(const char *line)
{
    for (; *line != '\0'; line++)
    {
        if (!isspace((unsigned char)*line))
        {
            return false; // achou caractere que não é espaço, linha não é vazia
        }
    }
    return true; // só espaços e/ou fim da string
}

void trim(char *str)
{
    int start = 0;
    int end = strlen(str) - 1;
    while (isspace(str[start]))
    {
        start++;
    }

    while (end >= start && isspace(str[end]))
    {
        end--;
    }
    if (start > end)
    {
        str[0] = '\0';
        return;
    }

    int i, j;
    for (i = start, j = 0; i <= end; i++, j++)
    {
        str[j] = str[i];
    }
    str[j] = '\0';
}