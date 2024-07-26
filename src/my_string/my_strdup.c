#include <main_header.h>

char* my_strdup(char* str)
{
    int len = my_strlen(str);
    if (len == 0)
    {
        return NULL;
    }
    char* new_str = malloc(sizeof(char) * (len + 1));
    if (new_str == NULL)
    {
        return NULL;
    }
    my_memcpy(new_str, str, len);
    new_str[len] = '\0';
    return new_str;
}