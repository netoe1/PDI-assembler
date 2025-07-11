#include "utils.h"
#include <string.h>
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

void print_slash(char *str)
{
    int i = 0;
    while (1)
    {
        if (str[i] == '\0')
        {
            printf("\\0");
            break;
        }
        printf("%c", str[i]);
        i++;
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
