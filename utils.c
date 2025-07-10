#include "utils.h"

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